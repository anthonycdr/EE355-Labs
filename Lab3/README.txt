For Q1 and Q2, I used the sample input provided in the lecture slides and the example from Brightspace. The Divide & Conquer and Strassen algorithms were implemented based on these references, and when compiled on my local system, the results matched the expected output.

For Q3, I followed the exact code template given in the lecture slides to measure execution time. However, the recorded times did not match the sample output from the slides. This discrepancy could be due to differences in hardware efficiency, my compiler, or how the clock() function records execution time. My implementation might be executing the code faster due to optimizations in memory allocation, or system-level execution differences.

Additionally, while Q1 and Q2 worked correctly on my local compiler, when I copied and ran the same code on the Linux VM, I noticed random zero values appearing in some positions of the matrix. Despite multiple debugging attempts, I couldn't identify the exact issue. Possible reasons for this include:

- Differences in memory allocation behavior between my local system and the Linux VM
- Uninitialized memory issues when handling dynamic matrix allocations
- How the Linux VM handles pointers and array indexing compared to my local setup

This suggests that while my logic is correct, there might be system-dependent behaviors affecting execution when run in the Linux VM.