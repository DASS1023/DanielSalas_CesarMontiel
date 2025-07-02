function valueN = inputNorm(value, minValue, maxValue)
  valueN = 2*(value-minValue)/(maxValue-minValue)-1;
endfunction
