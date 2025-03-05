package race_condition;

import java.util.concurrent.Semaphore;

class ResourceManager3 
{
    private static final int MAX_RESOURCES = 5;
    private int availableResources = MAX_RESOURCES;
    private Semaphore semaphore; 

    public ResourceManager3() 
    {
        this.semaphore = new Semaphore(MAX_RESOURCES, true); 
    }

    public void decreaseCount(int count) 
    {
        try 
        {
            semaphore.acquire(count); 
            synchronized (this) 
            {
                availableResources -= count;
                System.out.println(Thread.currentThread().getName() + " allocated " + count + " resources, Remaining: " + availableResources);
            }
        } 
        catch (InterruptedException e) 
        {
            e.printStackTrace();
        }
    }

    public void increaseCount(int count) 
    {
        synchronized (this) 
        {
            availableResources += count;
            System.out.println(Thread.currentThread().getName() + " released " + count + " resources, Remaining: " + availableResources);
        }
        semaphore.release(count);
    }
}

class Process3 extends Thread 
{
    private ResourceManager3 manager;
    private int request;

    public Process3(ResourceManager3 manager, int request) 
    {
        this.manager = manager;
        this.request = request;
    }

    @Override
    public void run() 
    {
        manager.decreaseCount(request);

        try {
            Thread.sleep(1000); // Simulate process execution
        } catch (InterruptedException e) {}

        manager.increaseCount(request);
    }
}

public class SemaphoreDemo {
    public static void main(String[] args) {
        ResourceManager manager = new ResourceManager();
        Thread t1 = new Process(manager, 3);
        Thread t2 = new Process(manager, 4);

        t1.start();
        t2.start();

        try {
            t1.join();
            t2.join();
        } catch (InterruptedException e) {}

        System.out.println("Final available resources: " + manager.availableResources);
    }
}


public class RaceCondition3 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

}
