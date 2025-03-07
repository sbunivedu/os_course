### **Exploring Linux Cryptography**

#### **Objective:**
Gain practical experience with Linux cryptographic tools by exploring cryptographic hashing, asymmetric key generation and usage, public key operations, and at-rest protection. Students will be able to verify file integrity, generate and use asymmetric keys for signing and encryption, and protect data at rest using encryption tools.

### **Activity Overview**
You will work through three main parts:

1. **Cryptographic Hashing:**
   Learn how to compute and verify file integrity using SHA-256 hashing.

2. **Asymmetric Key Generation and Usage:**
   Generate a GnuPG key pair, use it to sign and encrypt files, and verify signatures and decrypt messages.

3. **At-Rest Data Protection:**
   Encrypt a file (or create an encrypted container) using OpenSSL to protect data stored on disk.

### **Part 1: Cryptographic Hashing**

**Step 1: Create a Sample File**
- Open a terminal and create a text file:
  ```bash
  echo "This is a secret message." > secret.txt
  ```

**Step 2: Compute the SHA-256 Hash**
- Use the `sha256sum` command:
  ```bash
  sha256sum secret.txt
  ```
- **Observation:** Note the generated hash value.

**Step 3: Verify Integrity**
- Modify the file slightly:
  ```bash
  echo "An extra line." >> secret.txt
  ```
- Recompute the hash:
  ```bash
  sha256sum secret.txt
  ```
- **Discussion:** Compare the two hash values. Discuss how even a small change alters the hash.

**Step 4: Automate Verification (Optional)**
- Create a simple script (`check_integrity.sh`) that stores the original hash and checks if the file remains unchanged.
  ```bash
  #!/bin/bash
  ORIGINAL_HASH="your_original_hash_here"
  CURRENT_HASH=$(sha256sum secret.txt | awk '{print $1}')

  if [ "$ORIGINAL_HASH" == "$CURRENT_HASH" ]; then
      echo "File integrity verified: hashes match."
  else
      echo "Warning: File integrity compromised! Hash mismatch."
  fi
  ```
- Make the script executable:
  ```bash
  chmod +x check_integrity.sh
  ```

---

### **Part 2: Asymmetric Keys and Public Key Operations**

**Step 1: Generate a GnuPG Key Pair**
- Generate a new key pair:
  ```bash
  gpg --full-generate-key
  ```
- Follow the prompts to choose key type (default RSA and RSA is fine), key size, expiration, and identity information (name, email, etc.).

**Step 2: Sign a File**
- Create a sample file:
  ```bash
  echo "This document is confidential and has been signed." > document.txt
  ```
- Sign the file:
  ```bash
  gpg --clearsign document.txt
  ```
- **Observation:** A new file (e.g., `document.txt.asc`) is created containing the signed text.

**Step 3: Verify the Signature**
- Verify the signature:
  ```bash
  gpg --verify document.txt.asc
  ```
- **Discussion:** Note how GnuPG confirms the authenticity of the file and the signer’s identity.

**Step 4: Encrypt and Decrypt a File**
- Encrypt the file using your public key:
  ```bash
  gpg --encrypt --recipient your_email@example.com document.txt
  ```
- This produces `document.txt.gpg`.
- Decrypt the file:
  ```bash
  gpg --decrypt document.txt.gpg > decrypted.txt
  ```
- **Observation:** Compare `document.txt` and `decrypted.txt` to ensure they are identical.

---

### **Part 3: At-Rest Data Protection Using OpenSSL**

**Step 1: Create a File to Encrypt**
- Create a sample file:
  ```bash
  echo "Sensitive data that needs protection at rest." > data.txt
  ```

**Step 2: Encrypt the File with OpenSSL**
- Encrypt the file using AES-256:
  ```bash
  openssl enc -aes-256-cbc -salt -in data.txt -out data.txt.enc
  ```
- **Prompt:** Enter and verify a passphrase when prompted.

**Step 3: Decrypt the File**
- Decrypt the file:
  ```bash
  openssl enc -d -aes-256-cbc -in data.txt.enc -out data_decrypted.txt
  ```
- **Observation:** Verify that `data_decrypted.txt` matches the original `data.txt`.

**Step 4: Discussion of At-Rest Protection**
- **Discussion:** How does encrypting a file protect data at rest?
- What are the advantages and potential pitfalls of using file-level encryption for securing data on disk?

---

### **Wrap-Up and Reflection**

1. **Documentation:**
   - Write a lab report that includes:
     - A summary of the commands executed and their outputs.
     - Screenshots or terminal logs demonstrating each step.
     - Reflections on what was learned about cryptographic hashing, key management, and file encryption.

2. **Discussion Questions:**
   - Why is a cryptographic hash a reliable method for verifying file integrity?
   - What are the benefits and challenges of using asymmetric cryptography for secure communications?
   - How does at-rest encryption help secure sensitive data, and what best practices should be followed to manage encryption keys securely?
