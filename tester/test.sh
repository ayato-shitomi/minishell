#!/bin/bash

#=============================================================#

TEST_DIR=`pwd`
clear
cd ..
make re
DIR=`pwd`

RS=$TEST_DIR/result_log.md
F1=$TEST_DIR/minishell_stdout
F2=$TEST_DIR/bash_stdout

echo "`date`" > $RS

#============================================================#

function write_back_qote()
{
	echo '```' >> $RS
}

function runtest()
{
	clear
	
	echo "$@ > $F1" | ./minishell 2>&-
	echo "$@ > $F2" | bash 2>&-

	DIFF=`diff $F1 $F2`
	if [ $? -ne 0 ]; then
		echo "## $@ : >> KO << " >> $RS
		echo "" >> $RS
		echo "minishell" >> $RS
		write_back_qote
		cat $F1 >> $RS
		write_back_qote
		echo "bash" >> $RS
		write_back_qote
		cat $F2 >> $RS
		write_back_qote
	else
		echo "## $@ : OK" >> $RS
	fi
	sleep 0.1
	clear
}

#=============================================================#

runtest 'echo hello'
runtest 'echo "hello world"'
runtest 'echo $?'
runtest 'echo "$?"'
runtest 'echo '$?''
runtest 'echo "hello"world hello'

runtest 'exit'
runtest 'exit 1'
runtest 'exit 1 2 3'
runtest 'exit hello'
runtest 'exit 1 test'
runtest 'exit "hello world"'


runtest 'pwd'

runtest 'cd ..'
runtest 'cd ~'

runtest 'ls'
runtest 'ls -la'

#=============================================================#

glow $RS
