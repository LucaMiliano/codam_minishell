**MOETEN we fixen (staat in eval sheet)**
- echo $s returned altijd 0, ook na falen voorgaande command. (Echo $? + $? moet ook kloppen)
- na blocking commands (cat zonder augs of grep bijv) > CTRL C double prompt, CTRL \ missing message: "^\Quit (core dumped)"
- ">" blijft hangen en echo woord > naam.txt dumped trash in .txt. bestand. Voor ">>" geldt exact het zelfde
<!-- - Piping gaat nog niet helemaal goed:
ls | cat greptest.txt
1
2
3
4
5
cat: '': No such file or directory // dit zou er niet moeten staan

ander voorbeeld:
cat << EOF | cat | cat | wc -c telt niet het aantal chars maar doet gwn cat
- cat | cat | ls moet stoppen na 2 enters -->

**Kunnen we fixen (voor de hand liggende tests)**
- unclosed quotes laten blijven lezen ipv error message. Werkt eigenlijk hetzelfde als heredoc maar dan closing quotes ipv "EOF"
- na veranderen $USER (export) zou de naam in de prompt NIET moeten veranderen, dat gebeurt nu wel.
- cat << EOF < onbestaand.txt zou na EOF moeten zeggen dat onbestaand.txt niet bestaat
