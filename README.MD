<h1 align="center">
    <img alt="Pipex" src="https://game.42sp.org.br/static/assets/achievements/pipexe.png" width="200px" />
</h1>

# Pipex

This project help 42 students to have a deeper knowledge about processes and redirection.

## Execution

With Make installed just run `make` in the terminal to compile the program:
```bash
make
```

Then execute the program using the following rules:
`./pipex infile cmd1 cmd2 outfile`, the program should behave like the shell command `< infile cmd1 | cmd2 > outfile`.


### Examples

```bash
./pipex infile "ls -l" "wc -l" outfile # emulation
< infile ls -l | wc -l > outfile       # bash
```
```bash
make
./pipex infile "grep a1" "wc -w" outfile # emulation
< infile grep a1 | wc -w > outfile       # sh
```



### Note

I'm uploading too the files to debug inside vscode, because I don't want to lose the configuration.
