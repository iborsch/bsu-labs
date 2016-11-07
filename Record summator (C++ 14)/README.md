This program goes through a file and sums field of records with the same key.
Each field is a tuple of values that support the operation of adding.
Each key is a tuple of values that support the operation of comparing.
Assumed that all records have the same number and types of values in the key and the same in the field. 

Example of a file:  
Paris 14 2016 189  
Paris 15 2016 304  
Paris 16 2015 789  
Bern 17 2017 59  
Bern 17 2015 897  
Tallinn 18 2014 546  
Tallinn 19 2014 0  
Tallinn 19 2014 11
 
If the key is 1st and 3rd values, the field is 2nd and 4th values,
then output file should look like this:  
Paris 29 2016 493 (<- sum of the first two records)  
Paris 16 2015 789  
Bern 17 2017 59  
Bern 17 2015 897  
Tallin 56 2014 557 (<- sum of the last three records)  

Records must be sorted by the key.

Data at positions that are not the key or the field positions is equal to the corresponding data in the first record with this key.

You can set a condition, in this case, only records satisfying this condition will be processed.