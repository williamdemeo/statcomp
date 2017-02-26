% Matlab code sweeptest.m
%
% Written by William De Meo on Dec 17, 1997
%                Last Modified, Dec 17, 1997
%
% Inputs:
%          n number of rows
%          p number of covariates
%
% The following ensures that sweep.c gets the same answers
% regardless of whether the lower triangle is filled.
%
% Generate samples random matrices
% Generate random matrix X
X=randn(n,p);
% Form pxp SSCP matrix:
S = X'*X;
% Write S to SSCP to be read by column:
fid = fopen('SSCP','w');
       fprintf(fid,'%f\n',S);
       fclose(fid);

% zero out lower triangle:       
for i = 1:p
  S(i+1:p,i)=zeros(p-1,1);
end
% Write upper triangle of S to SSCPU:
fid = fopen('SSCPU','w');
       fprintf(fid,'%f\n',S);
       fclose(fid);
