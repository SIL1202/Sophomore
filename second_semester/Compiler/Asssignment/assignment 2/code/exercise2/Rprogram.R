# Create Table 1: Student-Main
# <-: meaning assignment operator in R
# c(): concatenate function to create vectors
# stringsAsFactors: Don't convert the string into factor, keep the character
student_main <- data.frame(
  StudentID = c(920121001, 920121002, 920121003, 920121004, 920121005,
                920121006, 920121007, 920121008, 920121009, 920121010,
                920121011, 920121012, 920121013, 920121014, 920121015,
                920121016, 920121017, 920121018),
  Name = c("Andy", "Bob", "Cecil", "Dennis", "Edward", "Felix", "Gigi", "Helen",
           "Iris", "Jane", "Kate", "Liz", "Martin", "Nancy", "Oscar",
           "Pattie", "Quinn", "Rebecca"),
  PaymentType = c(
    "A", "B", "C", "A", "B", "C", "B", "B", "B", "A", "B", "C",
    "A", "B", "C", "B", "B", "B"
  ),
  stringsAsFactors = FALSE
)

# Create Table 2: Fees
fees <- data.frame(
  PaymentType = c("A", "B", "C"),
  AmountRequired = c(0, 21345.00, 42690.00)
)

# Create Table 3: Student-Payment
student_payment <- data.frame(
  StudentID = c(920121005, 920121009, 920121003, 920121017, 920121012,
                920121002, 920121014, 920121018, 920121011, 920121006,
                920121015, 920121008),
  AmountPaid = c(21345.00, 21345.00, 42690.00, 21345.00, 21345.00,
                 21345.00, 15000.00, 21345.00, 20000.00, 42690.00,
                 21345.00, 10000.00)
)

# Merge to include PaymentType and required Amount
# merge(x = tableA, y = tableB, by = "column_name", all.x =, all.y =, all =
merged_data <- merge(
  student_main, fees,
  by = "PaymentType"
)
merged_data <- merge(
  merged_data, student_payment,
  by = "StudentID", all.x = TRUE
)

# Replace NA in AmountPaid with 0 (means no payment)
# $: is the way R selects columns
merged_data$AmountPaid[is.na(merged_data$AmountPaid)] <- 0

# Computation #1: Total amount received
total_received <- sum(merged_data$AmountPaid)
cat("Total amount received before due:", total_received, "\n\n")

# Computation #2: Students who underpaid
# create a new column ShortAmount to find out how much each student is short
# subset(x, subset, select) # nolint: commented_code_linter.
# x is data frame, subset is a logical condition, select is the columns to keep
merged_data$ShortAmount <- merged_data$AmountRequired - merged_data$AmountPaid
underpaid <- subset(
  merged_data,
  ShortAmount > 0,
  select = c("StudentID", "Name", "ShortAmount")
)

# cat() is a function in R that outputs text to the console, similar to print,
# but more concise, without the extra quotes or print constructs.
cat("Students who did not pay the required fees with the short amount:\n")
print(underpaid, row.names = FALSE)