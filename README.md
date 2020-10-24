# PacSnake

comp2012h best course

## git cheatsheet

### Better way: GitHub Desktop

Who still uses git in CLI lmao, get GitHub Desktop and let it do all the work for you :D (Includes instant diff checker!)

### Download the repo

If you need to clone (download) this repository from the GitHub server to your machine:

- Navigate to the folder in which you want the files in the repository to be stored.
- Execute `git clone https://github.com/54D/PacSnake.git` to clone via HTTPS.

### Modifying the code

After you've made changes to the code on your machine and you want to upload your progress:

- Execute `git add .` to add every file to the staging area.
- Execute `git commit -m <message>` to commit all the staged files. Now, your local repository contains the changes.
- Execute `git push` to add all your local commits to the remote repository (GitHub repository).

In the rare case we are very very organized and wish to use branches:

- If the branch you want to switch to...
    - ...already exists: `git switch <branch_name>`
    - ...doesn't exist yet: `git switch -c <new_branch_name>`
- Most likely you don't want to bring your changes to the branch you're switching to.
    - So, be sure to execute `git stash` first if you don't want carryover changes. This stores all your changes in a stack and allows you to work with a directory that doesn't contain the changes you just made.
    - See the list of stashed changes with `git stash list`.
    - Apply the most recent stashed change to the branch you currently are in with `git stash apply`.

### Sync your progress

Before you work on the project it's a good idea to make sure your local copy is up-to-date. Execute `git pull` and if you see merge conflicts good fucking luck lmao.

Alternatively if you just want to get the new changes without merging yet, `git fetch` is your friend.