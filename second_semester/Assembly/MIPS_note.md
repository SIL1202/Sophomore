# MIPS syscall、暫存器與記憶體操作總整理

---

## syscall 的運作方式

MIPS 中的 `syscall` 由 `$v0` 決定執行的動作：

| `$v0` 值 | 功能           | 需要的參數暫存器 | 說明                     |
|----------|----------------|------------------|--------------------------|
| `1`      | print int      | `$a0`            | 輸出整數                 |
| `4`      | print string   | `$a0`            | 輸出字串（記憶體地址）   |
| `5`      | read int       | (無)             | 輸入整數，結果放在 `$v0` |
| `10`     | exit program   | (無)             | 結束程式                 |

重點：**`syscall` 只會根據 `$v0` 來選擇功能，然後去讀對應暫存器的值**

---
### Example:

## 1. 最標準的輸出結構（三行法則）

    li $v0, 1               # 指定功能（1 = print int）
    li $a0, 123             # 把資料放到 $a0
    syscall                 # 執行


## 2. 輸出字串 
    
    li $v0, 4 
    la $a0, message (字串的地址)
    syscall

## 3. 讀入數字
    
    .data
    num1 = .word 0
    
    .text
    .global main
    main:
        li $v0, 5 
        syscall             # 將使用者輸入存在$v0
        la $t0, num1
        sw $v0, 0($t0)

## 4. 結束程式
    
    li $v0, 10
    syscall


    la $t0, num1 = {

        int num;

        int *t0 = &num;

    }

    lw $t1, 0($t0) = {

        int t1 = *t0;

    }

    sw $t2, 0($t0) = {

        *t0 = t2;    

    }
