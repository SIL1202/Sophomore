# Create Table 1: Student-Main
# <-: meaning assignment operator in R
# c(): concatenate function to create vectors
# stringsAsFactors: Do Not automatically convert the string into factor, keep the character # nolint
# read CSV files
student_main <- read.csv("HW2-PL-Data/HW2-Student-Main.csv", stringsAsFactors = FALSE) # nolint
fees <- read.csv("HW2-PL-Data/HW2-Fees.csv", stringsAsFactors = FALSE)
student_payment <- read.csv("HW2-PL-Data/HW2-Student-Payment.csv", stringsAsFactors = FALSE) # nolint

names(student_payment)[names(student_payment) == "Amount"] <- "AmountPaid"
names(fees)[names(fees) == "Amount"] <- "AmountRequired"

# convert the amount string(there is a comma at thousands digit) into numbers
student_payment$AmountPaid <- as.numeric(gsub(",", "", student_payment$AmountPaid)) # nolint
fees$AmountRequired <- as.numeric(gsub(",", "", fees$AmountRequired))

# Merge to include PaymentType and required Amount
# merge(x = tableA, y = tableB, by = "column_name", all.x = ..., all.y = ..., all = ...) # nolint
merged_data <- merge(student_main, fees, by = "Payment.Type")
merged_data <- merge(merged_data, student_payment, by = "Student.ID", all.x = TRUE) # nolint

# Replace NA in AmountPaid with 0 (means no payment)
# $: is the way R selects columns
merged_data$AmountPaid[is.na(merged_data$AmountPaid)] <- 0

# Computation #1: Total amount received
total_received <- sum(merged_data$AmountPaid)
cat("Total amount received before due:", total_received, "\n\n")

# Computation #2: Students who underpaid
# create a new column ShortAmount to find out how much each student is short
merged_data$ShortAmount <- merged_data$AmountRequired - merged_data$AmountPaid

# subset(x, subset, select), x is the data frame, subset is a logical condition, select is the columns to keep # nolint
underpaid <- subset(merged_data, ShortAmount > 0, select = c("Student.ID", "Name", "ShortAmount")) # nolint
# cat() is a function in R that outputs text to the console, similar to print,
# but more concise, without the extra quotes or print constructs.
cat("Students who did not pay the required fees with the short amount:\n")
print(underpaid, row.names = FALSE)
