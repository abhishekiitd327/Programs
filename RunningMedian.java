import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class RunningMedian{

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        Comparator<Integer> minComparator = new Comparator<Integer>(){
            public int compare(Integer a, Integer b){
                if(a<b) return -1;
                if(a>b) return 1;
                return 0;
            }
        };
        Comparator<Integer> maxComparator = new Comparator<Integer>(){
            public int compare(Integer a, Integer b){
                if(a>b) return -1;
                if(a<b) return 1;
                return 0;
            }
        };
        PriorityQueue<Integer> minHeap = new PriorityQueue<Integer>(n/2 + 1, minComparator);
        PriorityQueue<Integer> maxHeap = new PriorityQueue<Integer>(n/2 + 1, maxComparator);
        double median = 0;
        for(int i=0; i < n; i++){
            int x = in.nextInt();
            int minHeapSize = minHeap.size();
            int maxHeapSize = maxHeap.size();
            if(x < median){ // to be added to max Heap
                if(minHeapSize < maxHeapSize){
                    minHeap.add(maxHeap.poll());
                    maxHeap.add((Integer)x);
                    median = (double)(maxHeap.peek() + minHeap.peek())/2;
                } else if(maxHeapSize < minHeapSize){
                    maxHeap.add((Integer)x);
                    median = (double)(maxHeap.peek() + minHeap.peek())/2;
                } else {
                    maxHeap.add((Integer)x);
                    median = (double)(maxHeap.peek());
                }
            } else { // x >= median -- insert to min Heap
                if(minHeapSize < maxHeapSize){
                    minHeap.add((Integer)x);
                    median = (double)(minHeap.peek() + maxHeap.peek())/2;
                } else if(minHeapSize == maxHeapSize){
                    minHeap.add((Integer)x);
                    median = (double)(minHeap.peek());
                } else {
                    maxHeap.add(minHeap.poll());
                    minHeap.add((Integer)x);
                    median = (double)(minHeap.peek() + maxHeap.peek())/2;
                }
            }
            System.out.println(median);
        }
    }
}
