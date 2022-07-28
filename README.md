# Minishell

## 概要

このプロジェクトでは、Shellの再実装を行います。この課題はすべてCで書かれます。Unixのシグナルやプロセスの扱い方、Cのメモリ管理等の技術を身につけました。

## 使い方

## 技術的解説

### 仕様可能な関数

これらの関数のみの仕様が許可されます。

> readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

### 入力の扱い方

入力された文字列は最初にスペース区切りで配列に格納されます。
その後、配列の1つの要素を見た際に`"`,`'`,`>`,`<`,`$`が来たら分ける。
分ける際には以下のように解析する。
> - クォーテーションが来たら、クォーテーションが来るまで読み込む。それのタイプを`EXPANDABLE_QUOTED`に設定する
> - リダイレクトが来たら、それのタイプを`REDIRECT`に設定する
> - `$`が来たら`"`もしくは` `が来るまでを配列に入れる。それのタイプを`ENVIRONMENT_VAL`に設定する
これらを配列に格納する。

タイプ分けに関しては以下がヘッダーファイル（`includes/minishell.h`）に定義されています。

|数値|タイプ|意味|
|----|----|----|
|0|EXPANDABLE|展開可能、もしくは文字列|
|1|EXPANDABLE_QUOTED|ダブルクオートに囲われている展開可能|
|2|NOT_EXPANDABLE|展開不可能、シングルクオートに囲われてる|
|3|PIPE|パイプ|
|4|REDIRECT|リダイレクト|
|5|ENVIRONMENT_VAL|環境変数|

例えば以下のように扱います。

与えられる文字列。
```
echo USERNAME:"Mr $USER".>test
```

スペース区切りの配列を作成する。

|配列番号|文字列|
|----|----|
|0|echo|
|1|USERNAME:"Mr $USER".>test|

スペース区切りの配列を解析して、タイプ付きで解析する。

|配列番号|文字列|タイプ|
|----|----|----|
|0|echo|EXPANDABLE|
|1|USERNAME:|EXPANDABLE|
|2|Mr $USER|EXPANDABLE_QUOTED|
|3|.|EXPANDABLE|
|4|>|REDIRECT|
|5|test|EXPANDABLE|

### ToDo テストケース

- `"`,`'`,`>`,`<`,`$`のみのコマンドを入力したときのテスト

## 参考資料

<a src="./subject/subject.pdf">サブジェクトはこちら</a>
https://github.com/ayato-shitomi/minishell/blob/master/subject/subject.pdf
<a src="./subject/scale.md">レビュースケールはこちら</a>
https://github.com/ayato-shitomi/minishell/blob/master/subject/scale.md

## MTG議事録

### 7/17 9:00~

とりあえず参考にする構文解析が決定した。
https://rio-1.hatenablog.com/entry/2021/10/05/182916

ブランチ戦略については、明日話す。

### 7/18 11:00~

大まかな流れを確認した。
スケールを持ってきた。
Shell名は`Fresh`とする。

#### git

ブランチは使わず、PushPullする際に連絡することにする。
作業前にPullして、Push前に別ディレクトリへPullした後、作業内容を移動させてPushする。

#### 入力されたコマンドのあつかい方

`echo Hello I am "JUN" 'san' | cat`

Token	Type
echo	EXPANDABLE
Hello	EXPANDABLE
am		EXPANDABLE
JUN		EXPANDABLE_QUOTED
san		NON_EXPANDABLE
|		PIPE
cat		EXPANDABLE

`TYPE`分けについては、別途考える必要があり

```c
# define EXPANDABLE 10

typedef	s_hoge {
	int		type;
	char	*token;
}	t_hoge;

t_hoge	*command_list[];
```

https://jun-networks.hatenablog.com/entry/2021/07/02/034002

#### 作業内容

ashitomi
- pushswap提出
- makefile
- 起動処理
mhida
- 疑問点をまとめる
- Type分けをやる、字句解析、構文解析とう

### 7/19 8:00~

#### Git戦略

結局ブランチ切ることにした。
`feat_...`の形で切っている。

#### 昨日やったこと

起動処理ができた、`makefile`の修正

#### アルゴリズム

コマンドをスペース区切りで`malloc()`で確保したら、シグナル割り込み時にフリーできない。そのため、**グローバル変数で割り込みが起こったかのフラグ**を立てておく。

### 7/23 15:00~

#### 字句解析について

手順は
> 1)スペース区切り<br>
2) 要素を解析して、タイプ分けと格納

与えられた文字列
```
echo USERNAME:"Mr $USER".>test
```

スペース区切りで配列に格納

```
[0]	echo
[1]	USERNAME:"Mr $USER".>test
```

スペース分けされた配列の要素1つを読み込む際、`"`,`'`,`>`,`<`,`$`が来たら分けるようにする
要素の1つを解析する際、
- クォーテーションが来たら、クォーテーションが来るまで読み込む。それのタイプを`EXPANDABLE_QUOTED`に設定する
- リダイレクトが来たら、それのタイプを`REDIRECT`に設定する
- `$`が来たら`"`もしくは` `が来るまでを配列に入れる。それのタイプを`ENVIRONMENT_VAL`にする

```
[0]	echo		EXPANDABLE
[1]	USERNAME:	EXPANDABLE
[2]	Mr $USER	EXPANDABLE_QUOTED
[3]	.			EXPANDABLE
[4]	>			REDIRECT
[5]	test		EXPANDABLE
```

#### シグナル

割り込み時の処理については、質問したので回答待ち。
`sigaction()`と`signal()`についても質問した。

### 7/28 13:00~

#### Mallocできなかった場合

`exit(1)`で返すことにする。

#### トークンとデータの保持

双方向循環リストを採用する

### 7/30 20:00~
