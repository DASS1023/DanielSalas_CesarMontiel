function retval = tansig (input1)
   retval = (exp(input1)-exp(-input1))./(exp(input1)+exp(-input1));
end
