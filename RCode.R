data = read.table("TOAK.data", header = FALSE, sep = ";");
data = t(data[1:length(data)-1])
print("Probbility to do a Three Of A King in 3 tosses or less:")
length(data[data <= 3])/length(data)
hist(data[data < 11], main = "Repartition of the amount of tosses needed to do a Three Of A King", sub = "(Cropped to 10 tosses)" ,xlab = "Number of tosses", breaks = 0:10)
abline(v = mean(data), col = "red")
abline(v = 3, col ="gray")
text(mean(data),0,paste("mean=",mean(data)), col = "red",adj = c(-0.1,1.2))

data = read.table("full.data", header = FALSE, sep = ";");
data = t(data[1:length(data)-1])
print("Probbility to do a full in 3 tosses or less:")
length(data[data <= 3])/length(data)
hist(data[data < 31], main = "Repartition of the amount of tosses needed to do a Full", sub = "(Cropped to 30 tosses)" ,xlab = "Number of tosses", breaks = 0:30)
abline(v = mean(data), col = "red")
abline(v = 3, col ="gray")
text(mean(data),0,paste("mean=",mean(data)), col = "red",adj = c(-0.1,1.2))

data = read.table("FOAK.data", header = FALSE, sep = ";");
data = t(data[1:length(data)-1])
print("Probbility to do a Four Of A King in 3 tosses or less:")
length(data[data <= 3])/length(data)
hist(data[data < 16], main = "Repartition of the amount of tosses needed to do a Four Of A King", sub = "(Cropped to 15 tosses)" ,xlab = "Number of tosses", breaks = 0:15)
abline(v = mean(data), col = "red")
abline(v = 3, col ="gray")
text(mean(data),0,paste("mean=",mean(data)), col = "red",adj = c(-0.1,1.2))

data = read.table("ss.data", header = FALSE, sep = ";");
data = t(data[1:length(data)-1])
print("Probbility to do a Small Straight in 3 tosses or less:")
length(data[data <= 3])/length(data)
hist(data[data < 11], main = "Repartition of the amount of tosses needed to do a Small Straight", sub = "(Cropped to 10 tosses)" ,xlab = "Number of tosses", breaks = 0:10)
abline(v = mean(data), col = "red")
abline(v = 3, col ="gray")
text(mean(data),0,paste("mean=",mean(data)), col = "red",adj = c(-0.1,1.2))

data = read.table("ls.data", header = FALSE, sep = ";");
data = t(data[1:length(data)-1])
print("Probbility to do a Large Straight in 3 tosses or less:")
length(data[data <= 3])/length(data)
hist(data[data < 31], main = "Repartition of the amount of tosses needed to do a Large Straight", sub = "(Cropped to 30 tosses)" ,xlab = "Number of tosses", breaks = 0:30)
abline(v = mean(data), col = "red")
abline(v = 3, col ="gray")
text(mean(data),0,paste("mean=",mean(data)), col = "red",adj = c(-0.1,1.2))

data = read.table("yams.data", header = FALSE, sep = ";");
data = t(data[1:length(data)-1])
print("Probbility to do a Yams in 3 tosses or less:")
length(data[data <= 3])/length(data)
hist(data[data < 31], main = "Repartition of the amount of tosses needed to do a Yams", sub = "(Cropped to 30 tosses)" ,xlab = "Number of tosses", breaks = 0:30)
abline(v = mean(data), col = "red")
abline(v = 3, col ="gray")
text(mean(data),0,paste("mean=",mean(data)), col = "red",adj = c(-0.1,1.2))

print("Graphs in Rplots.pdf")
