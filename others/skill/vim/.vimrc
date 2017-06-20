set nocompatible 						"是否兼容VI，compatible为兼容，nocompatible为不完全兼容 
										"如果设置为compatible，则tab将不会变成空格 
"
set backspace=indent,eol,start			"
"indent: 如果用了:set indent,:set ai 等自动缩进，想用退格键将字段缩进的删掉，必须设置这个选项。否则不响应。
"eol:如果插入模式下在行开头，想通过退格键合并两行，需要设置eol。
"start：要想删除此次插入前的输入，需设置这个。
"
set mouse=a 							"设置在哪些模式下使用鼠标功能，mouse=a 表示所有模式
set backspace=2 						"设置 Backspace 和 Delete 的灵活程度，backspace=2 则没有任何限制 
set nowrap  							"不自动换行 
set autoindent 							"自动缩进
set shortmess=atI 						"启动的时候不显示那个援助索马里儿童的提示
behave mswin 							"设置鼠标运行模式为WINDOWS模式 
language messages zh_CN.utf-8 			"解决consle输出乱码 
"
set ai! 								"设置自动缩进 
set cindent shiftwidth=4 				"缩进的字符个数 
"set autoindent shiftwidth=2 
set showmatch 							"在输入括号时光标会短暂地跳到与之相匹配的括号处，不影响输入 
set formatoptions+=mM 					"正确地处理中文字符的折行和拼接 
set bsdir=buffer 						"设定文件浏览器目录为当前目录 
set autochdir 							"自动切换当前目录为当前文件所在的目录 
"set autoread			 				"自动重新加载外部修改内容 
"set paste 								"置粘贴模式，这样粘贴过来的程序代码就不会错位了。 
set clipboard+=unnamed 					"共享剪贴板 
"
" From Big Mu.
" ---------- vim configuration ----------
set t_Co=256                            " terminal supports 256 colors
set encoding=utf-8                      " utf-8 coding
syntax on                               " highlight syntax
set number                              " display line number
set cursorline                          " highlight current line
set showcmd                             " show incomplete command
set showmatch                           " match when typing () or []
set matchtime=2                         " 匹配括号高亮的时间（单位是十分之一秒） 0.2s 
set ruler                               " enable window ruler
"set lines=30 columns=100               " default window height and width
set scrolloff=5                         " set 5 lines visible at least when moving up or down
set cmdheight=2                         " cmd height equals 2
set laststatus=2                        " always show the statusline
set statusline=[%F]%y%r%m%*%=\|\ %l/%L,%c\ \|\ %p%%\ \|
set expandtab                           " 用空格代替tab 
autocmd FileType make set noexpandtab   " adopt tab when editting make file
set tabstop=4                           " TAB equals 4 spaces
autocmd FileType html set tabstop=2
set softtabstop=4                       " backspace equals -4 spaces
autocmd FileType html set softtabstop=2
set autoindent                          " 自动缩进 
set shiftwidth=4                        " auto indentation width
autocmd FileType html set shiftwidth=2
set cin                                 " 'V&=' autoalignment
"set list                               " show special chars (tab^I, trail$)
"set nolist                             " don't show special chars
set listchars=tab:?\ ,trail:?           " set tab and trail
"set mouse=a                             " set mouse available (SHIFT to paste)
set backspace=indent,eol,start          " enable backspace
set whichwrap=b,s,<,>,[,]               " move among consective lines (visual & insert mode)
set incsearch                           " search when typing
set hlsearch                            " highlight when searching
set gdefault                            " global substitution
"set ignorecase                         " 搜索忽略大小写 
"
"
"状态行颜色 
"highlight StatusLine guifg=SlateBlue guibg=Yellow 
"highlight StatusLineNC guifg=Gray guibg=White 
"
"