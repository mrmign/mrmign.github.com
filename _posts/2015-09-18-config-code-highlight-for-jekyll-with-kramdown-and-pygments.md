---
layout: post
title: "jekyll个性化配置"
categories: Tools
tags: jekyll, kramdown, pygments
---

## 软件版本

~~~ text

jekyll 2.5.3
Liquid 3.0.6
kramdown-1.8.0
pygments.rb-0.6.3
rake-10.4.2
hz2py-1.0.0  # 将中文转化为拼音

~~~


## 代码高亮问题

在使用jekyll的时候模板一直使用的Liquid，像下面这样的

~~~ text
{ % highlight lang linenos%}
code
{ % endhighlight %}
~~~


关于Liquid对于其他标签的解析这里不做深入探讨，只对使用`pygements`对代码高亮处理进行说明。如果要使用上述的代码高亮方式，就得每次都要填写同样的代码块，如果要显示行号也要添加对应的linenos标志，否则最终生成的代码块是不带行号的。这里对jekyll自带的代码高亮相关代码(`highlight.rb`, 在`jekyll-2.5.3/lib/jekyll/tags`目录下)进行分析，：

~~~ ruby
module Jekyll
  module Tags
    class HighlightBlock < Liquid::Block
      include Liquid::StandardFilters

      # The regular expression syntax checker. Start with the language specifier.
      # Follow that by zero or more space separated options that take one of three
      # forms: name, name=value, or name="<quoted list>"
      #
      # <quoted list> is a space-separated list of numbers
      SYNTAX = /^([a-zA-Z0-9.+#-]+)((\s+\w+(=(\w+|"([0-9]+\s)*[0-9]+"))?)*)$/

      def initialize(tag_name, markup, tokens)
        super
        if markup.strip =~ SYNTAX
          @lang = $1.downcase
          @options = {}
          if defined?($2) && $2 != ''
            # Split along 3 possible forms -- key="<quoted list>", key=value, or key
            $2.scan(/(?:\w="[^"]*"|\w=\w|\w)+/) do |opt|
              key, value = opt.split('=')
              # If a quoted list, convert to array
              if value && value.include?("\"")
                  value.gsub!(/"/, "")
                  value = value.split
              end
              @options[key.to_sym] = value || true
            end
          end
          @options[:linenos] = "inline" if @options.key?(:linenos) and @options[:linenos] == true
          #@options[:linenos] = "inline" 
          #@options[:lineanchors] = true
        else
          raise SyntaxError.new <<-eos
Syntax Error in tag 'highlight' while parsing the following markup:

  #{markup}

Valid syntax: highlight <lang> [linenos]
eos
        end
      end

      def render(context)
        prefix = context["highlighter_prefix"] || ""
        suffix = context["highlighter_suffix"] || ""
        code = super.to_s.strip

        is_safe = !!context.registers[:site].safe

        output =
          case context.registers[:site].highlighter
            when 'pygments'
              render_pygments(code, is_safe)
            when 'rouge'
              render_rouge(code)
            else
              render_codehighlighter(code)
            end

        rendered_output = add_code_tag(output)
        prefix + rendered_output + suffix
      end

      def sanitized_opts(opts, is_safe)
        if is_safe
          Hash[[
            [:startinline, opts.fetch(:startinline, nil)],
            [:hl_linenos,  opts.fetch(:hl_linenos, nil)],
            [:linenos,     opts.fetch(:linenos, nil)],
            [:encoding,    opts.fetch(:encoding, 'utf-8')],
            [:cssclass,    opts.fetch(:cssclass, nil)]
          ].reject {|f| f.last.nil? }]
        else
          opts
        end
      end

      def render_pygments(code, is_safe)
        require 'pygments'

        @options[:encoding] = 'utf-8'

        highlighted_code = Pygments.highlight(
          code,
          :lexer   => @lang,
          :options => sanitized_opts(@options, is_safe)
        )

        if highlighted_code.nil?
          Jekyll.logger.error "There was an error highlighting your code:"
          puts
          Jekyll.logger.error code
          puts
          Jekyll.logger.error "While attempting to convert the above code, Pygments.rb" +
            " returned an unacceptable value."
          Jekyll.logger.error "This is usually a timeout problem solved by running `jekyll build` again."
          raise ArgumentError.new("Pygments.rb returned an unacceptable value when attempting to highlight some code.")
        end

        highlighted_code
      end

      def render_rouge(code)
        require 'rouge'
        formatter = Rouge::Formatters::HTML.new(line_numbers: @options[:linenos], wrap: false)
        lexer = Rouge::Lexer.find_fancy(@lang, code) || Rouge::Lexers::PlainText
        code = formatter.format(lexer.lex(code))
        "<div class=\"highlight\"><pre>#{code}</pre></div>"
      end

      def render_codehighlighter(code)
        "<div class=\"highlight\"><pre>#{h(code).strip}</pre></div>"
      end

      def add_code_tag(code)
        # Add nested <code> tags to code blocks
        code = code.sub(/<pre>\n*/,'<pre><code class="language-' + @lang.to_s.gsub("+", "-") + '" data-lang="' + @lang.to_s + '">')
        code = code.sub(/\n*<\/pre>/,"</code></pre>")
        code.strip
      end

    end
  end
end

Liquid::Template.register_tag('highlight', Jekyll::Tags::HighlightBlock)

~~~

在解析md时对于代码段会进行是否显示行号的判断`@options[:linenos] = "inline" if @options.key?(:linenos) and @options[:linenos] == true` 并且默认使用inline的格式，就是行号与代码在一起，如果要复制代码，行号也会一起被选中复制。我们可以根据这个判断条件，直接自动添加显示行号的标记，我们这里不使用inline，使用lineanchors，让行号与代码分开。

~~~ ruby
#@options[:linenos] = "inline" if @options.key?(:linenos) and @options[:linenos] == true
@options[:lineanchors] = true
~~~

直接注释掉原来判断行号显示的代码，添加上面的代码，我们就会让jekyll在解析代码块的时候自动添加显示行号。如果要使用上面的方法，需要个性jekyll的lib，这样不是很通用。可以复制上面的`highlight.rb`到博客的`_plugins`目录下，修改`highlight.rb` 如下所示：

~~~ ruby
module Jekyll
  module Tags
    class CustomeHighlightBlock < Liquid::Block #因为jekyll的lib里有相同类的定义，这里修改为其他类名
      include Liquid::StandardFilters

      # The regular expression syntax checker. Start with the language specifier.
      # Follow that by zero or more space separated options that take one of three
      # forms: name, name=value, or name="<quoted list>"
      #
      # <quoted list> is a space-separated list of numbers
      SYNTAX = /^([a-zA-Z0-9.+#-]+)((\s+\w+(=(\w+|"([0-9]+\s)*[0-9]+"))?)*)$/

      def initialize(tag_name, markup, tokens)
        super
        if markup.strip =~ SYNTAX
          @lang = $1.downcase
          @options = {}
          if defined?($2) && $2 != ''
            # Split along 3 possible forms -- key="<quoted list>", key=value, or key
            $2.scan(/(?:\w="[^"]*"|\w=\w|\w)+/) do |opt|
              key, value = opt.split('=')
              # If a quoted list, convert to array
              if value && value.include?("\"")
                  value.gsub!(/"/, "")
                  value = value.split
              end
              @options[key.to_sym] = value || true
            end
          end
          @options[:lineanchors] = true  # 要修改的地方
        else
          raise SyntaxError.new <<-eos
Syntax Error in tag 'highlight' while parsing the following markup:

  #{markup}

Valid syntax: highlight <lang> [linenos]
eos
        end
      end

      
    end
  end
end

Liquid::Template.register_tag('highlight', Jekyll::Tags::CustomeHighlightBlock) #因为jekyll的lib里有相同类的定义，这里修改为其他类名

~~~

根据上面的代码进行相应修改即可。剩下的就是要个性CSS样式了，可以根据[这个]( http://drewsilcock.co.uk/proper-linenumbers/ )来修改，本文中的代码样式就是根据该链接进行修改的。

我在配置的时候使用的是`kramdown`来解析markdown文件的，就是像github那样的使用`~~~ lang  ~~~`的代码块格式，这里可以通过使用一个开源的插件[kramdown-with-pygments](https://github.com/mvdbos/kramdown-with-pygments)来支持代码高亮，添加了该插件后还要进行一定的修改，因为该插件里有自己对代码块的解析及输出最终的html，这个与前面我们自己修改的highlight.rb有些许冲突。因为`highlight.rb`是针对Liquid里的标签tag进行识别处理的，这里的是直接进行converter处理，修改如下：

~~~ ruby
def convert_codeblock(el, indent)
    attr = el.attr.dup
    lang = extract_code_language!(attr) || @options[:kramdown_default_lang]
    code = pygmentize(el.value, lang)
    # code_attr = {}
    # code_attr['class'] = "language-#{lang}" if lang
    # "#{' '*indent}<div class=\"highlight\"><pre#{html_attributes(attr)}><code#{html_attributes(code_attr)}>#{code}</code></pre></div>\n"

    code = code.sub(/<pre>\n*/,'<pre><code class="language-' + lang + '" data-lang="' + lang + '">')
    code = code.sub(/\n*<\/pre>/,"</code></pre>")
    code.strip
  end

def convert_codespan(el, indent)
    attr = el.attr.dup
    lang = extract_code_language!(attr) || @options[:kramdown_default_lang]
    code = pygmentize(el.value, lang)
    # if lang
    #   attr['class'] = "highlight"
    #   if attr.has_key?('class')
    #     attr['class'] += " language-#{lang}"
    #   else
    #     attr['class'] = "language-#{lang}"
    #   end
    # end
    # "<code#{html_attributes(attr)}>#{code}</code>"
    "<code>#{code}</code>"
  end
~~~

经过上面的处理，两种代码高亮方式就都支持了。说了这么多，要解决的问题就是如何使用`pygments`对代码进行高亮显示，并默认添加行号。通过这次的修改过程，对jekyll的一些代码高亮处理的逻辑有所了解了，但是jekyll依赖的其他的库还不了解。同时也勾起了对ruby的学习兴趣，如今使用ruby开发的各种便利工具有很多，如`cocoapods`，`jekyll`等，学习下ruby还是有很多好处的。

## 在创建新的文章时title是中文时自动转拼音问题

在创建新的文章时，要填写title，这个title也会在文章内填写好，jekyll默认不支持非ascii码的title，这里使用了`hz2py` 这个gem， 在`Rakefile`里对 post task进行相应修改。 这样就可以直接在title里填写中文了。

~~~ ruby
task :post do
  abort("rake aborted: '#{CONFIG['posts']}' directory not found.") unless FileTest.directory?(CONFIG['posts'])
  title = ENV["title"] || "new－post"
  # 新增用来接收category和description参数
  category = ENV["category"] || ""
  description = ENV["description"] || ""
  tags = ENV["tags"] || "[]"
  # 新增用来将汉字转换成拼音，因为url好像不支持中文。当然在文件顶部require了Hz2py
  slug = Hz2py.do(title, :join_with => '-', :to_simplified => true)
  ...
end # task :post
~~~

附上解决问题过程中遇到的关于jekyll的好资源供大家学习：

* [jekyll官网](https://jekyllrb.com), [jekyll官网中文](http://jekyllcn.com/) 
* [Jekyll QuickStart](http://jekyllbootstrap.com/usage/jekyll-quick-start.html)
* [中文title转拼音](http://www.soooldier.com/blog/2013/04/27/gai-jin-jekyll-bootstrapde-rakefile/)
* [kramdown-with-pygments](https://github.com/mvdbos/kramdown-with-pygments)
* [jekyll主题](http://jekyllthemes.org/themes/uno-dbyll/) 这里有很多，可以自己选择中意的



