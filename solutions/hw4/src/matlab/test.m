prob1
x= X(:,1);
y = X(:,2);
theta = [30, 0.065]
F = zeros(8,1);
for i=1:8,
F(i) = (theta(1) * x(i))/(theta(2) + x(i));
end
J = zeros(8,2);
for i=1:8,
J(i,1) = x(i)/(theta(2) + x(i));
J(i,2) = -theta(1)*x(i)/((theta(2) + x(i))*(theta(2) + x(i)));
end
[Q,R] = qr(J)
z = y - F;
delta = J\z;

% New
theta = theta' + .5 * delta;
F = zeros(8,1);
for i=1:8,
F(i) = (theta(1) * x(i))/(theta(2) + x(i));
end
J = zeros(8,2);
for i=1:8,
J(i,1) = x(i)/(theta(2) + x(i));
J(i,2) = -theta(1)*x(i)/((theta(2) + x(i))*(theta(2) + x(i)));
end
J
z = y - F;
delta = J\z