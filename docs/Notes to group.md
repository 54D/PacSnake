
## First steps to Qt	

### Installation	

Steps:	
1. Head to Qt's download section: https://www.qt.io/download.	
2. Scroll down and click **Go open source**.	
3. Scroll down and click **Download the Qt Online Installer**.	
4. Click **Download**. The file is around 22,400 KB.	
5. Open the installer, and go through the sections one by one. Some (probably) important options include:	
    - You need to register a free Qt account upon reaching the **Welcome** section.	
    - Expect around gigabytes of files to be downloaded in total, so choose a custom installation location if needed in the **Installation Folder** section.	
    - Important -- In **Select Components** section, you need to manually select the components to download. The default options are not enough. 	
        + In Qt --> Developer and Designer Tools, select a MinGW distribution. For instance, I selected MinGW 8.1.0 x64.	
        + In Qt --> Qt (any verison), select the SAME MinGW distribution. For instance, I selected Qt 5.15.1 --> MinGW 8.1.0 x64	
    - The rest are straightforward enough. Aggregating all the necessary tools to download, the total size should not reach 5 GB.	
6. Now wait and do whatever you want, there'll be a lot of files downloaded.	

Useful links:	
- No useful kits found: https://forum.qt.io/topic/84198/no-valid-kits-found or https://stackoverflow.com/questions/26499404/	

### Project init	

Useful links: 	
- Qt quick project kickstart: https://doc.qt.io/qtcreator/quick-projects.html	

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