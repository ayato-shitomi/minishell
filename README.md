# Minishell

## 概要

このプロジェクトでは、２人チームでShellの再実装を行います。この課題はすべてC言語で書かれます。Unixのシグナルやプロセスの扱い方、Cのメモリ管理等の技術を身につけました。

メンバー：[mhida](https://github.com/mhidaa)、[ashitomi](http://github.com/ayato-shitomi)

## 使い方

![runShell](./readme/runShell.gif)

このアプリケーションを利用するためには`readline`がインストールされている必要があります。

```
> brew install readline
```

### コンパイルと起動

```shell
> make
> ./minishell
```

素晴らしいSHELL「Fresh」へようこそ！

## 技術的解説

### 仕様可能な関数

これらの関数のみの仕様が許可されます。

> readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

### 組み込み関数

以下の組み込み関数をサポートしています。

|関数|説明|例|
|---|---|---|
|echo|文字列を出力する|`echo "hello world"`|
|exit|Shellを終了する|`exit`<br>`exit 3`|
|env|環境変数を表示する|`env`|
|export|環境変数を表示する、セットする|`export`<br>`export PRICE=100`|
|unset|環境変数をクリアする|`unset PRICE`|
|cd|ディレクトリを移動する|`cd HogeHoge`<br>`cd ~`|
|pwd|カレントディレクトリを表示する|`pwd`|

## その他

チェック、テストしたケースはこちらです。
[チェック項目](./readme/scale.md)

ミーティングの議事録を載せています。
[MTG議事録](./readme/mtg.md)
