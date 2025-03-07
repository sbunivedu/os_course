### **Exploring Linux Security – Setuid, sudo, ACLs, and Capabilities**

#### **Objective:**
Gain hands-on experience with Linux security mechanisms by exploring and manipulating file permissions (including the setuid bit), configuring sudo privileges, and working with access control lists (ACLs) and capabilities. Students will learn how these features enhance security and control user privileges.

#### **Part 1: Exploring Setuid Bits**

**1. Inspecting File Permissions and Setuid:**
- Open a terminal and run:
  ```bash
  ls -l /usr/bin/passwd
  ```
  **Observation:** Notice the permission string (e.g., `-rwsr-xr-x`), where the `s` in the user execute position indicates the setuid bit is set.

**2. Creating a Simple Test Program:**
- Create a file named `showuids.c` with the following content:
  ```c
  #include <stdio.h>
  #include <unistd.h>

  int main() {
      printf("Real UID: %d, Effective UID: %d\n", getuid(), geteuid());
      return 0;
  }
  ```
- Compile the program:
  ```bash
  gcc -o showuids showuids.c
  ```

**3. Running the Program as a Regular User:**
- Execute:
  ```bash
  ./showuids
  ```
  **Observation:** Both real and effective UID should be your own.

**4. Setting the setuid Bit:**
- Change ownership to root (requires sudo):
  ```bash
  sudo chown root:root showuids
  sudo chmod u+s showuids
  ```
- Run the program again:
  ```bash
  ./showuids
  ```
  **Observation:** The effective UID should now be 0 (root) while the real UID remains your user ID.
- **Discussion:** Why is it important to limit the use of setuid and ensure that only trusted programs use this mechanism?

#### **Part 2: Understanding sudo**

**1. Reviewing sudo Configuration:**
- Open the sudoers file using:
  ```bash
  sudo visudo
  ```
- **Observation:** Examine how privileges are defined (e.g., the `%sudo` group). Note the syntax and security rules applied.

**2. Running Commands with sudo:**
- Try running a command with sudo:
  ```bash
  sudo ls /root
  ```
  **Observation:** You should be prompted for your password. This demonstrates how sudo elevates privileges for specific commands without fully switching to the root user.

**3. Configuring Custom sudo Privileges (Optional Challenge):**
- Create a custom command file (e.g., a script that displays system status), then configure sudo to allow a particular user to run it without a password.
- **Example:**
  - Create `sysstatus.sh`:
    ```bash
    #!/bin/bash
    echo "System Status:"
    uptime
    free -h
    ```
  - Make it executable:
    ```bash
    chmod +x sysstatus.sh
    ```
  - Edit the sudoers file via `sudo visudo` and add:
    ```
    your_username ALL=(ALL) NOPASSWD: /path/to/sysstatus.sh
    ```
  - Test with:
    ```bash
    sudo /path/to/sysstatus.sh
    ```

#### **Part 3: Working with Access Control Lists (ACLs) and Capabilities**

**1. Viewing ACLs on Files:**
- Choose a test file or create one:
  ```bash
  touch testfile.txt
  ls -l testfile.txt
  ```
- View the current ACLs:
  ```bash
  getfacl testfile.txt
  ```

**2. Setting ACLs:**
- Grant read permission to a specific user (replace `username` with an actual user):
  ```bash
  sudo setfacl -m u:username:r testfile.txt
  ```
- Verify the new ACL:
  ```bash
  getfacl testfile.txt
  ```
- **Discussion:** How do ACLs provide a more fine-grained control over file permissions compared to the traditional user/group/others model?

**3. Exploring Capabilities:**
- Capabilities allow binaries to have fine-grained privileges without granting full root permissions.
- Check capabilities on a binary (e.g., ping):
  ```bash
  getcap /bin/ping
  ```
- **Observation:** Note the capabilities assigned (e.g., `cap_net_raw+ep`).

**4. Setting Capabilities (Optional):**
- For an experimental binary (e.g., our custom binary `showuids`), try setting a capability (requires careful handling):
  ```bash
  sudo setcap cap_net_bind_service=+ep showuids
  ```
- Verify the change:
  ```bash
  getcap showuids
  ```
- **Discussion:** How do capabilities help limit the scope of privileges compared to setuid programs?

#### **Wrap-Up and Reflection:**

1. **Documentation:**
   - Write a short lab report detailing your commands, observations, and any challenges encountered.
   - Include screenshots or terminal logs as evidence of your work.

2. **Discussion Questions:**
   - What security risks are associated with setuid programs, and how does Linux mitigate these risks?
   - How does sudo provide controlled privilege escalation compared to a full root login?
   - In what scenarios would ACLs and capabilities be preferred over traditional permission models?
