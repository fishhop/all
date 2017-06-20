
########################  for git  ########################
alias gc='git commit -a -m'
alias gcam='git commit --amend -a -m'
alias gcamc='git commit --amend -a -C HEAD'
alias gc.='git commit -a -m "."'

alias gst='git status'
alias gps='git push'
alias gpl='git pull'
alias gad='git add -A'

alias gl='git log --pretty=format:"%cd    ---   %s  %C(auto)" -30 --date=format:%c'
alias gl5='git log --pretty=format:"%cd    ---   %s  %C(auto)" -30 --date=format:%c -5'

alias gpla='
myPath=$PWD;
echo 【1】-----------------------------------;cd /cygdrive/d/fish/prime/; pwd; gpl; echo;
echo 【2】-----------------------------------;cd /cygdrive/d/fish/fishing/; pwd; gpl; echo; 
echo 【3】-----------------------------------;cd /cygdrive/d/fish/cpp/; pwd; gpl; echo;
cd $myPath'

alias gsta='
myPath=$PWD;
echo 【1】-----------------------------------;cd /cygdrive/d/fish/prime/; pwd; gst; echo;   
echo 【2】-----------------------------------;cd /cygdrive/d/fish/fishing/; pwd; gst; echo;
echo 【3】-----------------------------------;cd /cygdrive/d/fish/cpp/; pwd; gst; echo;
cd $myPath'

alias gpsa='
myPath=$PWD;
echo 【1】-----------------------------------;cd /cygdrive/d/fish/prime/; pwd; gps; sleep 1; echo;
echo 【2】-----------------------------------;cd /cygdrive/d/fish/fishing/; pwd; gps; sleep 1; echo; 
echo 【3】-----------------------------------;cd /cygdrive/d/fish/cpp/; pwd; gps; sleep 1; echo;
cd $myPath'


########################  开发  ########################
alias gcc='gcc -g -Wall -fdiagnostics-color=auto -std=c99'
alias g++='g++ -g -Wall -fdiagnostics-color=auto -std=c++11'

alias a='./*.exe'

alias ga='
echo ----------------------------------------------------------;
echo;echo "g++ *.cpp";echo;
rm *.exe;
g++ *.cpp;
echo ----------------------------------------------------------;
echo;echo "./*.exe";
echo ----------------------------------------------------------;
./*.exe'


########################  自定义命令  ########################
#win32
#eg: np test.cpp
alias np='/cygdrive/d/Program\ Files/Notepad++/notepad++.exe'
alias si='/cygdrive/c/Program\ Files/Source\ Insight\ 3/Insight3.exe'

#win64
#alias np='/cygdrive/d/Program\ Files\ \(x86\)/Notepad++/notepad++.exe'
#alias si='/cygdrive/d/Program\ Files\ \(x86\)/Source\ Insight\ 3/Insight3.exe'

#chrome
alias b='b.bat&'


########################  bash 命令  ########################
alias grep='grep --color=auto'
alias hs='history | grep --color=auto -i'

alias l='ls -ah --color=tty'
alias ll='ls -alh -nG --color=tty'   		#ls相关，这里--color需要根据终端设 
alias lt='ls -alht -nG --color=auto'        	#按修改时间查看目录下文件  

alias .='cd ../'
alias ..='cd ../../'

########################  环境配置  ########################
#日期时间格式
export TIME_STYLE='+%Y/%m/%d %H:%M:%S'

#为了gcc编译显示英文，但，设为英文后ls等显示中文乱码
#export LANG='en_US'
export LANG=zh_CN.UTF-8

#for GDB core dump
export CYGWIN='error_start=C:/cygwin/bin/dumper.exe'

#git log时区设置
TZ=UTC-8