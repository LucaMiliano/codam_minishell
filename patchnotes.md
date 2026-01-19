LP 5-1-2026
- write 'exit' bij exit command weggehaald
- paar compilatie errors mbt write length gefikst


TODO / bugs to fix
 - Wanneer CTRL + \ na cat zonder augs print: \Quit (core dumped) ipv alleen \
 - CTRL + C na cat zonder augs doet ook raar, print prompt 2x
 - export zet ook iets in de env wanneer het niet ergens naar verwijst: export hoi zou niks moeten doen, export hoi=hallo wel


 prompt.c > fgets vervangen

 BUG:
 meerdere commands over meerdere lines laten uitvoeren:

 ls
/bin/ls
nosuchcommand
echo $?

bovenstaand zou gewoon moeten werken bijvoorbeeld.

NOG EEN BUG:
echo hello world
echo ""
echo ""

zie deze chat voor een hoop buggy commands die we moeten fixen:
https://chatgpt.com/share/696e2ce7-675c-8010-b912-77b44b93de8b