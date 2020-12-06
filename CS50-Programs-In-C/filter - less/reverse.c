// Function to reverse elements of an array
void reverse(int arr[], int n)
{
	for (int low = 0, high = n - 1; low < high; low++, high--)
	{
		int temp = arr[low];
		arr[low] = arr[high];
		arr[high] = temp;
	}
}