function [W1,b1,W2,b2,emedio]=neuralTrain(P,T,nodeHidden,fhidden,foutput)

Q=size(P,2); % Cantidad de ejemplos

inputs=size(P,1); %
outputs=size(T,1); % Numero de neuronas en una capa
 

W1=rand(nodeHidden,inputs); %Pesos
b1=rand(nodeHidden,1); % Biases

W2=rand(outputs,nodeHidden); %Pesos
b2=rand(outputs,1); % Biases
      
% Tasa de aprendizaje
alfa = 0.001;


for Epocas = 1:500  % Correr el algoritmo de optimazacion durante 1000 repeticiones
    sum = zeros(outputs,1); % valor inicial de la suma de los errores
    for i = 1:Q % Algoritmo de optimizacion
        q=randi(Q);
        % Propagación hacia adelante
        if fhidden=='tansig' & foutput=='tansig'
            a1 = tansig(W1*P(:,q) + b1);
            a2 = tansig(W2*a1 + b2);
           % Retropropagación de la sensibilidades
            e = T(:,q)-a2; % error de prediccion
            s2 = -2*diag((1-a2.^2))*e; % sensibilidad de la ultima capa
            s1 = diag((1-a1.^2))*W2'*s2; % sensibilidad de la capa oculta
        elseif fhidden=='tansig' & foutput == 'logsig'
            a1 = tansig(W1*P(:,q) + b1);
            a2 = logsig(W2*a1 + b2);
           % Retropropagación de la sensibilidades
            e = T(:,q)-a2; % error de prediccion
            s2 = -2*diag((1-a2).*a2)*e; % sensibilidad de la ultima capa
            s1 = diag((1-a1.^2))*W2'*s2; % sensibilidad de la capa oculta
        elseif fhidden=='logsig' & foutput == 'logsig'
            a1 = logsig(W1*P(:,q) + b1);
            a2 = logsig(W2*a1 + b2);
           % Retropropagación de la sensibilidades
            e = T(:,q)-a2; % error de prediccion
            s2 = -2*diag((1-a2).*a2)*e; % sensibilidad de la ultima capa
            s1 = diag((1-a1).*a1)*W2'*s2; % sensibilidad de la capa oculta
        elseif fhidden=='logsig' & foutput == 'tansig'
            a1 = logsig(W1*P(:,q) + b1);
            a2 = tansig(W2*a1 + b2); 
            % Retropropagación de la sensibilidades
            e = T(:,q)-a2; % error de prediccion
            s2 = -2*diag((1-a2.^2))*e; % sensibilidad de la ultima capa
            s1 = diag((1-a1).*a1)*W2'*s2; % sensibilidad de la capa oculta
        elseif fhidden=='logsig' & foutput == 'linear'
            a1 = logsig(W1*P(:,q) + b1);
            a2 = W2*a1 + b2; 
           % Retropropagación de la sensibilidades
            e = T(:,q)-a2; % error de prediccion
            s2 = -2*e; % sensibilidad de la ultima capa
            s1 = diag((1-a1).*a1)*W2'*s2; % sensibilidad de la capa oculta
        elseif fhidden=='tansig' & foutput == 'linear'
            a1 = tansig(W1*P(:,q) + b1);
            a2 = W2*a1 + b2;
           % Retropropagación de la sensibilidades
            e = T(:,q)-a2; % error de prediccion
            s2 = -2*e; % sensibilidad de la ultima capa
            s1 = diag((1-a1.^2))*W2'*s2; % sensibilidad de la capa oculta
        else
            disp('Transfer funtion no define')
        end
        % Actualización de pesos sinapticos y bias
        W2 = W2 - alfa*s2*a1';
        b2 = b2 - alfa*s2;
        W1 = W1 - alfa*s1*P(:,q)';
        b1 = b1 - alfa*s1;  
        % Sumando el error cuadratico 
        sum = e.^2 + sum;
    end
    % Error cuadratico medio
    emedio(Epocas) = mean(sum)/Q;
    disp(Epocas);
end
end

