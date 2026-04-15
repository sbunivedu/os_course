# Exploring the File System

* Explain how files and directories are represented in the OS
* Distinguish between **hard links** and **symbolic links**
* Understand **inode-based file systems**
* Reason about how high-level commands map to low-level OS behavior

## Setup

Use a Linux environment (local machine, VM, or WSL).

Create a working directory:

```bash
mkdir fs_lab
cd fs_lab
```

# Part 1: Files and Inodes

## Step 1: Create a file

```bash
echo "Hello OS" > file1.txt
```

## Step 2: Inspect metadata

```bash
ls -li
```

**Observe:**

* The **inode number** (first column)

Now run:

```bash
stat file1.txt
```

**Questions**

* What is an inode?
* Which metadata is stored in the inode?
* Does the filename appear in the inode?

A **file name is just a mapping to an inode** (stored in a directory).

# Part 2: Hard Links

## Step 1: Create a hard link

```bash
ln file1.txt file2.txt
```

## Step 2: Inspect

```bash
ls -li
```
**Observe:**

* Same inode number for both files
* Link count increased

## Step 3: Modify one file

```bash
echo "New line" >> file2.txt
cat file1.txt
```

**Questions**

* Why does modifying one affect the other?
* What does the link count represent?

## Step 4: Delete one link

```bash
rm file1.txt
ls -li
cat file2.txt
```
**Questions**

* Why does the file still exist?
* When is the data actually deleted?

A file’s data is deleted only when:

* Link count = 0 **AND**
* No process has it open

# Part 3: Symbolic Links

## Step 1: Create a symbolic link

```bash
ln -s file2.txt file3.txt
```

## Step 2: Inspect

```bash
ls -li
```

**Observe:**

* Different inode
* Arrow notation (`file3.txt -> file2.txt`)

## Step 3: Break the link

```bash
rm file2.txt
cat file3.txt
```

**Questions**

* Why does the symbolic link break?
* What does it store internally?


## Key Insight

* Hard link → points to **inode**
* Symbolic link → points to **path name**

# Part 4: Directories as Mappings

## Step 1: Create a directory and files

```bash
mkdir dir1
touch dir1/a.txt dir1/b.txt
```

## Step 2: Inspect directory inode

```bash
ls -li dir1
```

## Step 3: View raw structure

```bash
ls -lai dir1
```

**Observe:**

* `.` (self)
* `..` (parent)

## Questions

* What is a directory really storing?
* How does the OS resolve paths like `/dir1/a.txt`?

## Key Insight

A directory is just a **mapping: filename → inode number**
