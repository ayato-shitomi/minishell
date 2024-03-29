# MTG議事録

## 7/17 9:00~

とりあえず参考にする構文解析が決定した。
https://rio-1.hatenablog.com/entry/2021/10/05/182916

ブランチ戦略については、明日話す。

## 7/18 11:00~

大まかな流れを確認した。
スケールを持ってきた。
Shell名は`Fresh`とする。

### git

ブランチは使わず、PushPullする際に連絡することにする。
作業前にPullして、Push前に別ディレクトリへPullした後、作業内容を移動させてPushする。


### 入力の扱い方

入力された文字列は最初にスペース区切りで配列に格納されます。
その後、配列の1つの要素を見た際に`"`,`'`,`>`,`<`,`$`が来たら分ける。
分ける際には以下のように解析する。
> - クォーテーションが来たら、クォーテーションが来るまで読み込む。それのタイプを`EXPANDABLE_QUOTED`に設定する
> - リダイレクトが来たら、それのタイプを`REDIRECT`に設定する
> - `$`が来たら`"`もしくは` `が来るまでを配列に入れる。それのタイプを`ENVIRONMENT_VAL`に設定する
('$'は字句解析時にはチェックせず、変数展開時にチェックする方針に変更)
これらを配列に格納する。

タイプ分けに関しては以下がヘッダーファイル（`includes/minishell.h`）に定義されています。

|数値|タイプ|意味|
|----|----|----|
|0|EXPANDABLE|展開可能、もしくは文字列|
|1|EXPANDABLE_QUOTED|ダブルクオートに囲われている展開可能|
|2|NOT_EXPANDABLE|展開不可能、シングルクオートに囲われてる|
|3|PIPE|パイプ|
|4|REDIRECT_LEFT_ONE|リダイレクト「<」|
|5|REDIRECT_RIGHT_ONE|リダイレクト「>」|
|6|REDIRECT_LEFT_TWO|リダイレクト「<<」|
|7|REDIRECT_RIGHT_TWO|リダイレクト「>>」|
|8|ENVIRONMENT_VAL|環境変数|

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
|4|>|REDIRECT_RIGHT_ONE|
|5|test|EXPANDABLE|


### 入力されたコマンドのあつかい方

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

### 作業内容

ashitomi
- pushswap提出
- makefile
- 起動処理
mhida
- 疑問点をまとめる
- Type分けをやる、字句解析、構文解析とう

## 7/19 8:00~

### Git戦略

結局ブランチ切ることにした。
`feat_...`の形で切っている。

### 昨日やったこと

起動処理ができた、`makefile`の修正

### アルゴリズム

コマンドをスペース区切りで`malloc()`で確保したら、シグナル割り込み時にフリーできない。そのため、**グローバル変数で割り込みが起こったかのフラグ**を立てておく。

## 7/23 15:00~

### 字句解析について

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
('$'は字句解析時にはチェックせず、変数展開時にチェックする方針に変更)

```
[0]	echo		EXPANDABLE
[1]	USERNAME:	EXPANDABLE
[2]	Mr $USER	EXPANDABLE_QUOTED
[3]	.			EXPANDABLE
[4]	>			REDIRECT_RIGHT_ONE
[5]	test		EXPANDABLE
```

### シグナル

割り込み時の処理については、質問したので回答待ち。
`sigaction()`と`signal()`についても質問した。

## 7/28 13:00~

### Mallocできなかった場合

`exit(1)`で返すことにする。

### トークンとデータの保持

双方向循環リストを採用する

## 7/30 20:00~

### トークンとデータの保持

字句解析のときのみ双方向循環リストを仕様する。
双方向循環リストは`*_dl_lst`の形を取る。

### 字句解析に関して

ダブルクオートが奇数個の処理に関しては、字句解析の先頭で`Syntax error`を出す。

```
> echo " " "
Syntax error
> 
```

### 変数展開の流れ

> 字句解析 → 構文解析の際に変数展開する

### SHELL変数

Shell変数→Shellが終わるまで入る変数。
```
> a="t e x t"
> echo $a
t e x t
```

考える必要ありそう！

## 8/9 17:30~

### `1>file`などの挙動について。

Shellによって挙動が全然ことなる。
リダイレクトの定義がされてないので、実装する必要はなし。
この様な形が来た場合には、未定義動作とする。

### シンタックスエラー

シンタックスエラーとして扱う条件

> ・`>`が来てからその後に何も来ない場合<br>
> ・`>`が２つ来る場合<br>
> ・リダイレクトの次にパイプが来る場合（パイプ後のリダイレクトは大丈夫）<br>
> ・１文字目がパイプの場合<br>

### グローバル変数について

終了ステータスを持つ変数としてグローバル変数を利用する。
終了ステータスを常時表示できると面白いかもですね。

## 8/11 17:30~

ヒアドキュメントの実装
Guacamoleの問題　→　解決

ashitomi：終了ステータスをとってこられるか調べる

## 8/15 17:00~

### ビルドインコマンド

ビルドインコマンドの終了ステータスはグローバル変数に格納する

### バグ

スペース１つだけのやつは解消

### 作業内容

ヒアドク２個以上とかの実装ができた
細かいエラー
ノルムエラーの対処

## 8/19 21:00~

### ビルドインコマンド

グローバル変数で解決する。

## 8/21 15:00~

### echo

### cd 

パイプがない場合には親プロセスで実行
ある場合にはFORKして実行（このときExitStatusが反映される）

### exportなど

パイプがない場合には、Forkせずに親プロセスの中で関数を実行
Bashパイプのなかは、FORKして、`ft_export`をうごかす。

### ビルドイン

パイプなしならフォークせずに、パイプありならフォークする
ExitStatusをちゃんと変える。

## 8/27 18:00~

### echo 

`info`をもらって`echo`のなかで処理するようにすればよい。

`echo`は２種類必要となる。

### unset

`t_env_var_lst`から要素を消せばよい。
引数は環境変数の名前のみ。

### 残りタスク

- ヒアドクの修正
- ノーム対応
- ユニットテストの作成

## 8/30 17:00~

### Bashからの起動時とZshからの起動時の挙動の確認

### unset

Unsetが呼び出せるようになった

### echo 

構文解析で環境変数を展開するから、Echoの中では触れなくて大丈夫そう

## 9/1 17:00~

### unset

あと、リストから要素を削除するのみ。

### BashとZsh

BashでExportが動かない、Zshでコマンドが受け渡せていない

### 残りタスク

残りタスクを洗い出すために、DiscordのToDoにどんどん書き込むことにします。


## 9/5 13:00~

### unset

- デバッグ用のSTDOUTを削除する。
- メモリーリークしてると思うから治す

### BashとZsh

- 一応解決した

### リーク関係

`-fsanitize=address`で処理すれば、リーク箇所がわかりやすい。

BashでExportはサニタイザーなくても落ちるから、対応すべき。
```
==6362==Hint: address points to the zero page.
    #0 0x10c3a80f0 in ft_strncmp (minishell:x86_64+0x1000010f0)
    #1 0x10c3c7b80 in get_env_value (minishell:x86_64+0x100020b80)
    #2 0x10c3ca102 in ft_export_case_no_arg (minishell:x86_64+0x100023102)
    #3 0x10c3c9f90 in ft_export (minishell:x86_64+0x100022f90)
    #4 0x10c3c5b78 in exec_builtin_without_pipe (minishell:x86_64+0x10001eb78)
    #5 0x10c3ab1b9 in set_fd_and_exec_builtin_without_pipe (minishell:x86_64+0x1000041b9)
    #6 0x10c3aad7f in execute_command (minishell:x86_64+0x100003d7f)
    #7 0x10c3aa1c5 in parse_command (minishell:x86_64+0x1000031c5)
    #8 0x10c3a7b91 in main (minishell:x86_64+0x100000b91)
    #9 0x7fff644783d4 in start (libdyld.dylib:x86_64+0x163d4)
```

### 対応済み

- 終了ステータス
- 構文解析
- export
- echo, unset

### 次の作業

- テスター作成
- export対応

## 9/9 17:00~

### 次の作業

- レビューで見られる点のチェック

特にリダイレクトとパイプ周りをチェックする。

## 9/11 16:00~

### 対応済み

- echo
- exit

## ToDo

- リダイレクトを使用したときの終了ステータス
- unset
- Norminette

unsetの対応とビルドインコマンドのNorminette対応をしようかなと。
コメントはすべて英語に翻訳します💪

## 9/11 21:00~

unset は終わり
BuiltのNorminetteもOK

## 9/12 21:00~

### ToDo

- Norminette
- レビュー項目のテスト

## 9/14 21:00~

- 字句解析
- Unset　環境変数自体を渡した際の挙動、エラーメッセージと`$?`の書き換え
- cd

## 9/15 21:00~

- unset 周りのエラー確認
- 字句解析等

## 9/16 20:00~

最終チェックをする。

## 9/20 21:00~

- パイプの直し
- リークのチェック等
