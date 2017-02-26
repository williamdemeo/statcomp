% MATLAB code tests.m
% Created by William J. De Meo
% on 11/28/97
%
% Purpose: test programs GS and GSpiv by duplicating them
%          in MATLAB, in particular on ill-conditioned data
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
% Generate random matrix A, starting with the SVD of a random matrix
format long;
m=100; n=100; cnd = 100;
  A=randn(m,n);
  [u,s,v]=svd(A);
% Let singular values range from 1 to cnd, with
% uniformly distributed logarithms
  sd = [1, cnd, exp(rand(1,n-2)*log(cnd))];
  s = diag(sd);
  A=u(:,1:n)*s*v';
%
% Write the matrix A to datafile:
fid = fopen('datafile','w');
       fprintf(fid,'%f\n',A);
       fclose(fid);

tt = cputime;
% Perform QR without pivoting:
[Q,R] = qr(A);
et = cputime - tt;
% R
disp(sprintf('time for MATLAB qr decomp (no-pivot): %7.4f sec',et));

tt = cputime;
% Perform QR with pivoting:
[Qpiv, Rpiv, P] = qr(A);
et = cputime - tt;
%Rpiv
%P
disp(sprintf('time for MATLAB qr decomp (pivot): %7.4f sec',et));
%
% END tests.m



