LP 5-1-2026
- write 'exit' bij exit command weggehaald
- paar compilatie errors mbt write length gefikst


TODO / bugs to fix
 - Wanneer CTRL + \ na cat zonder augs print: \Quit (core dumped) ipv alleen \
 - CTRL + C na cat zonder augs doet ook raar, print prompt 2x
 - export zet ook iets in de env wanneer het niet ergens naar verwijst: export hoi zou niks moeten doen, export hoi=hallo wel