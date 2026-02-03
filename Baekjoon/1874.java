import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Stack;

public class Main {
	public static void main(String[] args) throws Exception {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder sb = new StringBuilder();
		
		int N = Integer.parseInt(in.readLine());
		
		Stack<Integer> stack = new Stack<>();
		int start = 1;
		
		while(N-- > 0)
		{
			int target = Integer.parseInt(in.readLine());
			
			if(target >= start)
			{
				for(; start <= target; ++start)
				{
					stack.push(start);
					sb.append("+\n");
				}
			}
			
			if(stack.peek() != target)
			{
				System.out.println("NO");
				return;
			}
			
			stack.pop();
			sb.append("-\n");
		}
		
		System.out.println(sb);
	}
} 
