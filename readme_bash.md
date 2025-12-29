Just a file with random bash commands to learn and utilize
# this is sorting through manual heredoc
cpinas@f0r3s21:~$ cat << EOF | sort
> f
> d
> w
> a
> b
> c
> e
> g
> h
> i
> j
> k
> O
> l
> p
> m
> n
> q
> r
> s
> t
> u
> v
> z
> y
> x
> EOF
a
b
c
d
e
f
g
h
i
j
k
l
m
n
O
p
q
r
s
t
u
v
w
x
y
z
cpinas@f0r3s21:~$

the >> EOF (end of file idomatic not necesarry can be anything)
(inputdata)
EOF (is the start and the end with data in between for usadge)


Prompt for tomorrow:

"Hey ChatGPT, yesterday we finished the lexer and tokenization, including handling quotes, expandable tokens, and operators. We also defined the parser data structures (t_cmd and t_redir) and discussed how pipes create new commands. Now I want to start implementing the parser in C, step by step. Please help me write the parse() function and any necessary helper functions, keeping everything idiomatic for a minishell. Assume all my lexer functions and token structs are ready and correct. Let's start from parsing WORD tokens, building argv, handling redirections, and splitting commands by PIPE tokens."c
