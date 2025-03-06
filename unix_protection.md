## ***Unix Protection: Setuid and Root***

This assignment is designed to give students hands-on experience with file permissions, the setuid mechanism, and the distinction between the real and effective user IDs.

## **Objective:**
- Explore and understand the Unix protection system.
- Learn how file permissions and the setuid bit affect program behavior.
- Distinguish between real user ID and effective user ID.
- Observe how root privileges work in practice.

## **Prerequisites:**
- A Linux system or virtual machine with a Unix-like operating system (Ubuntu, Fedora, etc.).
- Basic familiarity with the command line.
- A text editor (e.g., `vim`, `nano`, or any preferred editor).
- A C compiler (e.g., `gcc`).

## **Lab Environment Setup:**
1. **Log in as a Regular User:**
   - Ensure you are logged in as a non-root user (e.g., `student`).

2. **Open a Terminal Window:**
   - You will execute all commands in the terminal.

3. **Create a Working Directory:**
   ```bash
   mkdir ~/unix_protection_lab
   cd ~/unix_protection_lab
   ```

## **Step-by-Step Instructions:**

### **Step 1: Examine File Permissions**
1. **List Files with Detailed Information:**
   Run the following command to view file permissions in your home directory:
   ```bash
   ls -l ~
   ```
   - **Observation:** Notice the permission strings (e.g., `-rwxr-xr-x`), which represent read, write, and execute permissions.

2. **Identify Files with Special Bits:**
   - Look for files with an `s` in the permission string. This indicates the setuid (or setgid) bit is set.
   - **Example:** System executables like `/usr/bin/passwd` often have the setuid bit set.

### **Step 2: Create a Test Program**
1. **Write a C Program to Display User IDs:**
   Open your favorite text editor and create a file named `myuid.c`:
   ```c
   #include <stdio.h>
   #include <unistd.h>

   int main() {
       printf("Real UID: %d, Effective UID: %d\n", getuid(), geteuid());
       return 0;
   }
   ```
2. **Save and Exit the Editor.**

3. **Compile the Program:**
   In your terminal, run:
   ```bash
   gcc -o myuid myuid.c
   ```
   - This will create an executable named `myuid`.

### **Step 3: Run and Observe Program Behavior**
1. **Run the Program as a Regular User:**
   Execute:
   ```bash
   ./myuid
   ```
   - **Observation:** Note the output. Both the **Real UID** and **Effective UID** should be your user’s ID.

2. **Set the setuid Bit on the Executable:**
   Change the ownership of the program to root (you may need to use `sudo` for this step):
   ```bash
   sudo chown root:root myuid
   sudo chmod u+s myuid
   ```
   - **Explanation:** Setting the setuid bit causes the program to run with the privileges of the file's owner (in this case, root).

3. **Run the Program Again:**
   ```bash
   ./myuid
   ```
   - **Observation:** This time, the **Effective UID** should be `0` (root), while the **Real UID** remains your user’s ID.
   - **Discussion Point:** What implications does this have for security? Why must setuid programs be written carefully?

### **Step 4: Reflection and Questions**
1. **Compare the Two Outputs:**
   - What is the difference between the real user ID and the effective user ID?
   - How does setting the setuid bit affect the program's privileges?

2. **Discussion Questions:**
   - Why is it important that only trusted programs have the setuid bit set?
   - What potential security vulnerabilities could arise if a setuid program is not properly coded?
   - How does the Unix protection system ensure that users cannot easily escalate privileges?

3. **Document Your Findings:**
   - Write a brief lab report summarizing your observations.
   - Include the commands you executed and the outputs you observed.
   - Reflect on the potential risks of setuid programs and how they are mitigated in a secure Unix system.
