% Code pour tracer le mouvement du robot
% S3 GRO
% Adapter les noms des fichiers
% Ajuster la taille de la zone affichée
% Ajuster la taille et position de l'obstacle

function TracerS3GRO()

S3GRO1 = load('S3GRO.1'); 
S3GRO2 = load('S3GRO.2'); 

% Redéfinition des variables lues dans le premier fichier
t = S3GRO1(:,1);
x = S3GRO1(:,2);
xp = S3GRO1(:,3);
q = S3GRO1(:,4);
qp = S3GRO1(:,5);
qgp = S3GRO1(:,6);
qdp = S3GRO1(:,7);
fg = S3GRO1(:,8);
fd = S3GRO1(:,9);
Ng = S3GRO1(:,10);
Nd = S3GRO1(:,11);
tau = S3GRO1(:,12);

% Redéfinition des variables lues dans le second fichier
xPos = [S3GRO2(:,1:2:8) S3GRO2(:,1)]; 
yPos = [S3GRO2(:,2:2:8) S3GRO2(:,2)]; 
xCcm = S3GRO2(:,9); 
yCcm = S3GRO2(:,10); 
xB = S3GRO2(:,11); 
yB = S3GRO2(:,12);
xWgContact = S3GRO2(:,13);
yWgContact = S3GRO2(:,14);
xWgContact = S3GRO2(:,15);
yWgContact = S3GRO2(:,16);

radiusWheel = abs(yPos(1,4) - yWgContact(1,1));

% Taille de la zone tracée
xmaxFigure = 2; 
xminFigure = -0.5; 
ymaxFigure = 0.5; 
yminFigure = -2; 

figure(1)

for i = 1:length(t)
    
    % Robot
    plot(xPos(i,:)',yPos(i,:)','-','LineWidth',2)
    hold on
    
    % Roues
    rectangle('Position',[xPos(i,4) - radiusWheel, yPos(i,4) - radiusWheel, radiusWheel*2, radiusWheel*2],...
        'Curvature',[1,1],...
        'FaceColor','w');
    rectangle('Position',[xPos(i,3) - radiusWheel, yPos(i,3) - radiusWheel, radiusWheel*2, radiusWheel*2],...
        'Curvature',[1,1],...
        'FaceColor','w');
    
    % Pendule
    plot([xCcm(i,1) xB(i,1)]', [yCcm(i,1) yB(i,1)]','-','LineWidth',2)
    
    % Obstacle
    rectangle('Position',[0.5,-0.5,0.01,0.285])
    
    % Masse
    plot([xB(i,1)]', [yB(i,1)]','o','LineWidth',2,'MarkerSize',5)

    % Trace de la masse
    plot(xB(1:i), yB(1:i),'-')
    
    % Sol
    line([xminFigure xmaxFigure], [0 0]);
    axis equal
    axis([xminFigure xmaxFigure yminFigure ymaxFigure])
    hold off
    
    pause(0.001)
    
    film(:,i) = getframe;
end
