# Minishell

## 仕様可能な関数

## 参考資料

<a src="./scale.md">レビュースケールはこちら</a>

## MTG議事録

### 7/17 9:00~

とりあえず参考にする構文解析が決定した。
https://rio-1.hatenablog.com/entry/2021/10/05/182916

ブランチ戦略については、明日話す。

### 7/18 ~~9:00~~~ 11:00~

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