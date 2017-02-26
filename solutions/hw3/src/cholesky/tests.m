% MATLAB code cholesky.m
%
%   datafile = A file containing the matrix tested
%   (so that we can run GS and GSpiv on the same matrix)
%
% Generate a random nxn matrix:
A=randn(n);
%
% Generate a random nxn spd matrix:
A = A'*A;
%
% Write the matrix A to datafile:
fid = fopen('datafile','w');
       fprintf(fid,'%f\n',A);
       fclose(fid);
% Perform Cholesky:
R = chol(A);
R'
%
% END tests.m



