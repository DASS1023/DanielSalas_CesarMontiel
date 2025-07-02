function a=neuralPredict(W,P,b,ftransfer)

if ftransfer=='tansig'
  a=tansig(W*P + b);  
elseif ftransfer=='logsig'
  a=logsig(W*P + b);  
elseif ftransfer=='linear'
  a=W*P + b;   
else
  disp('Transfer funtion no define')
  a=0;
end
end