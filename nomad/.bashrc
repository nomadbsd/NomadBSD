# some useful aliases
alias h='fc -l'
alias j=jobs
alias m=$PAGER
alias ll='ls -laFo'
alias l='ls -l'
alias g='egrep -i'
 
# # be paranoid
alias cp='cp -ip'
alias mv='mv -i'
alias rm='rm -i'


# set prompt: ``username@hostname$ '' 
PS1="`whoami`@`hostname | sed 's/\..*//'`"
case `id -u` in
	0) PS1="${PS1}# ";;
	*) PS1="${PS1}$ ";;
esac

