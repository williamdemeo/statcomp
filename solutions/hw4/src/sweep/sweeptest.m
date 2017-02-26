% MATLAB code sweeptest.m
% Created by William J. De Meo
% on 12/17/97
%
% Purpose: test program sweeptest.c and subroutine sweep.c by
%          generating a matrix and
%
% Inputs: 
%
%   m, n = numbers of rows, columns in test matrices
%          m should be at least n
%
%   cnd = condition number of test matrices to generate
%         (ratio of largest to smallest singular value)
%         cnd should be at least 1
%
% Outputs:
%
%   datafile = A file containing the matrix tested
%   (so that we can run GS and GSpiv on the same matrix)
%   
%   R = the R from the QR decomposition of A
% 
%   Rpiv, E = the R and permutation matrix E from QR decomposition 
%             of A with pivoting
%
% Read data from file data.m (which contains 5 X's and a Y)
data
% and put them in the same matrix X
X = [X,Y]; 
%

% Form 6x6 SSCP matrix:
S = X'*X;
% Write S to datafile to be read by column:
fid = fopen('SSCP','w');
       fprintf(fid,'%f\n',S);
       fclose(fid);

%  First easy check is the inverse:
iS = inv(S)

%
% END seeptest.m



