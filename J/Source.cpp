//The input of the device is the sequence { ai }.Then the following two operations are performed on it :
//We choose the interval[l; r] and perform ai ← ai^2mod2010 for all such i, that l ≤ i ≤ r.
//We choose the interval[l; r] and derive the sum of all ai such that l ≤ i ≤ r. Note that the sum is not calculated by modulo 2010.
//
//Input data
//
//The first line contains the length of the sequence n(1 ≤ n ≤ 50 000).
//The second line contains n numbers ai(0 ≤ ai ≤ 2009) specifying the initial sequence.
//The third line contains the number of operations m(1 ≤ m ≤ 50 000).Each of the following m lines describes the operation.
//The j - th operation is described by its type kj('1' is squaring, '2' is the sum calculation), 
//followed by two integers lj and rj(1 ≤ lj ≤ rj ≤ n).
//
//Output
//
//For each operation of the second type on a separate line, output a response.


//Optimization is critical point.




#include <iostream>
#include <algorithm>

using namespace std;

int *arr;

int *tree;


int pow2mod2010(int x)
{
	x *= x;
	int c = x % 5, d = x % 67;
	if (c % 2 != 0)
		c += 5;
	while (d % 30 != 0)
		d += 67;
	return (1005 * (x % 2) + 670 * (x % 3) + 201 * c + d) % 2010;
}



void build(int v, int tl, int tr)
{
	if (tl == tr)
		tree[v] = arr[tl];
	else {
		int v2 = v << 1, m = (tl + tr) >> 1;
		build(v2, tl, m);
		build(v2 + 1, m + 1, tr);
		tree[v] = tree[v2] + tree[v2 + 1];
	}
}

void update(int v, int tl, int tr, int l, int r)
{
	//if (l > r)
	//	return;
	if (tl == tr)
		tree[v] = pow2mod2010(tree[v]);
	else {
		int m = (tl + tr) >> 1, v2 = v << 1;
		int m1 = min(r, m), m2 = max(m + 1, l);
		if (l <= m1)
			update(v2, tl, m, l, m1);
		if (m2 <= r)
			update(v2 + 1, ++m, tr, m2, r);
		tree[v] = tree[v2] + tree[v2 + 1];
	}
}


int sum(int v, int tl, int tr, int l, int r)
{
	if (l > r)
		return 0;
	if (l == tl && r == tr)
		return tree[v];
	int m = (tl + tr) >> 1;
	int v2 = v << 1;
	return sum(v2, tl, m, l, min(r, m)) + sum(v2 + 1, m + 1, tr, max(m + 1, l), r);
}



int main()
{
	int n;
	cin >> n;
	arr = new int[n];
	tree = new int[4 * n];

	register int *array = &arr[0];
	//register int sum = 0;
	for (register int i = 0; i != n; ++i)
		cin >> array[i];

	build(1, 0, n - 1);

	int opers, operNum, l, r;
	cin >> opers;
	for (int i = 0; i < opers; ++i)
	{
		cin >> operNum >> l >> r;
		--l;
		--r;
		if (operNum != 1)
			cout << sum(1, 0, n - 1, l, r) << endl;
		else {
			update(1, 0, n - 1, l, r);
		}
	}
	return 0;
}