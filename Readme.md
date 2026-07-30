# 🏗️ SIDDHCESNA - II PRO 

**Type:** 16-bit Single-cycle ISA  
**Architecture:** 16-bit Unified Bus with Seprate Memory blocks for Instruction and Data 
**Instruction Width:** 16-bit  

---

## 1. System Overview

| Component | Specification |
| :--- | :--- |
| **Word Size** | 16-bit |
| **Address Space** | 12-bit (4,096 Words) |
| **General Purpose Registers** | 4 (R0, R1, R2, R3) |
| **ALU Feeders** | 2 Dedicated (RA, RB) |
| **Data Memory** | RAM (12-bit Address / 16-bit Data) |
| **Program Memory** | ROM (12-bit Address / 16-bit Instructions) |
| **TTY Display** | ASCII DISPLAY |

---

## 2. Instruction Formats (Type XX)

The architecture uses the two most significant bits **[15:14]** to determine the instruction type.

### Type 00: Unified Bus Move & ALU
Performs arithmetic/logic and moves the result or a raw register value across the bus.
* **Format:** `[Type:2][Opcode:4][Source:3][Dest:3][Unused:4]`
* **Logic:** `Dest = Source` (where Source is often the output of an ALU Op).

### Type 01: Direct Store (STR)
Stores a register value into a specific RAM location.
* **Format:** `[Type:2][RegID:2][Address:12]`
* **Logic:** `RAM[Addr] = Reg[ID]`

### Type 10: Control Flow (JUMP)
Jumps to a ROM address based on the comparison of RA and RB.
* **Format:** `[Type:2][Condition:2][Address:12]`
* **Logic:** `if (Condition) PC = Address`

### Type 11: Direct Load (LDR)
Loads an 16-bit constant into a register. 
* **Format:** `[Type:2][RegID:2][MemoryAddress:12]`
* **Logic:** `REG[r0-r3] = RAM[ADDRESS]` 

---

## 3. Component & Register Mapping (3-bit IDs)

These IDs are used as **Source** and **Destination** pointers in Type 00 instructions.

| ID | Mnemonic | Description |
| :--- | :--- | :--- |
| **000** | R0 | Register 0 |
| **001** | R1 | Register 1 |
| **010** | R2 | Register 2 |
| **011** | R3 | Register 3 |
| **100** | ALU_OUT | Result of the current ALU operation |
| **101** | RA | ALU Operand A (Input) |
| **110** | RB | ALU Operand B (Input) |
| **111** | CPU_OUT | TTY it Takes ASCII  |

---

## 4. ALU Opcode Table (Bits 13–10)

Defined for Type 00 instructions. All operations act on **RA** and **RB**.

| Opcode | Mnemonic | Operation |
| :--- | :--- | :--- |
| 0000 | ADD | RA + RB |
| 0001 | SUB | RA - RB |
| 0010 | MUL | RA * RB |
| 0100 | NOT | ~RA (Bitwise NOT) |
| 1000 | PASSA | Pass RA directly to Bus |
| 1001 | PASSB | Pass RB directly to Bus |
| 1111 | HALT | Stop CPU Execution |

---

## 5. Jump Conditions (Type 10)

| ID | Mnemonic | Condition |
| :--- | :--- | :--- |
| 00 | JZ | Jump if Zero (RA == RB) |
| 01 | JG | Jump if Greater (RA > RB) |
| 10 | JS | Jump if Smaller (RA < RB) |
| 11 | JC | Jump if Carry Flag |

---




**Author:** Siddhu70707  
**License:** MIT