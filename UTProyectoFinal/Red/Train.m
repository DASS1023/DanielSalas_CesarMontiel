%clc
%clear
close

%load DataSet.mat

nodeHidden=2;
outputs=2;

fhidden='tansig';
foutput='tansig';

%% Training
[W1,b1,W2,b2,emedio]=neuralTrain(P,T,nodeHidden,fhidden,foutput);
figure
plot(emedio)


%% Validacion
##
##Q=size(Test_input,2); % Cantidad de ejemplos
##
##for q = 1:Q % Red Neuronal
##  a1 = neuralPredict(W1,Test_input(:,q),b1,fhidden);
##  a2 = neuralPredict(W2,a1,b2,foutput);
##  e_validacion(q) = mean(Test_output(:,q)-a2); % error de prediccion
##end
##figure
##plot(e_validacion)

##save -mat7-binary 'Weight.mat' 'W1' 'b1' 'W2' 'b2' 'emedio'
