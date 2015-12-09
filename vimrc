"自动补全配置
filetype plugin indent on
set completeopt=longest,menu

"设置行号
set nu!

"设置taglist窗口
let Tlist_Show_One_File=1
let Tlist_Exit_OnlyWindow=1

"将taglist和netrw窗口整合到一起
let g:winManagerWindowLayout='FileExplorer|TagList'
nmap wm :WMToggle<cr>

"cscope配置
"cscope -Rbq
set cscopequickfix=s-,c-,d-,i-,t-,e-
"cscope add ~/open_src_proj/linux-source-3.2.0/cscope.out ~/open_src_proj/linux-source-3.2.0
cscope add ~/open_src_proj/redis-2.8.17/cscope.out ~/open_src_proj/redis-2.8.17

"设置tab宽度
set ts=4
set expandtab

"语法高亮
syntax enable
syntax on

"配色方案
"colorscheme desert

set cindent shiftwidth=4
