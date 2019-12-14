Clarkson CS142 project 2 submission 2019

Design Doc: https://docs.google.com/document/d/1pMU8ulzgSENBlzgmUQWd9QkUHwvDwexRRbuj2oKS7w4/edit?ts=5df4c4aa

Status Report:
The project is sooooo close to finished working. There's a chance you'll get to it before we can finish - so here's the current state of the project.

There's a very very strange memory glitch effecting almost every command. Some patterns of commands just cause the program to crash with 0xC0000005. For example (on my machine I have no reason to believe another would be different but it could be...) running "next next" causing a crash but "previous previous next next next" is fine. It also seems crashes happen with a releatively few amount of commands, ie running the last string of commands you can add abritary amount of "next" and "previous" and I haven't gotten it to crash. 

This memory error has inhibitted the abbilty to write searching. The logic on the underneath is in the source and even the UI is basically done but the damn 0xC0000005 is consistantly striking. Everything else has worked well so long as you're not unlucky and find a combination of commands that don't. Here's the break down.

1. Start a new season.
- We opted for saving and loading different files. 
- With "open" you can load data in from a save file and with "create" you can start a new game. Create will delete all the data previously stored in the file you're opening.

2. Next and Previous.
- Both "work" and they're circular. So long as you don't hit a bad combo.

3. Add a player.
- Run's logarithmically plus the constant for calculating the new index.
- Category is auto calculated

4. Edit a player.
- Proud of this gem. User can optionally choose to edit "name", "year", "status" or "all".

5. Delete a player.
- Run's logarithimcally.
- Ran into an issue with memory error (of course) and our work around was to set the selected player to index 0 after deleting.

6. Print list of players.
- "go-print", the formatting is pretty straight forward.

7. Display stats.
- "tell-stats" (can you tell we were running out of letters :). The origanal plan was to use filters but those never came to life. Right now we only have a simple "how many have paid out of the total"

8. Search for players.
- A lot of the code is written in the back end but sadly nothing really runs at the moment. There is a UI you can try to explore but you will eventually crash.

9. Exit the view mode.
- We were going to have a kind of "view buffer" where you could progessively search narrowing your fields. The command runs but crashes.

10. Stop the program.
- Again we did save and load method. Be sure to "save" before quitting!
