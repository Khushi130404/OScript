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
                System.out.println(Thread.currentThread().getName() + " allocated " + count + " resources, Remaining: " + getAvailableResources());
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
            System.out.println(Thread.currentThread().getName() + " released " + count + " resources, Remaining: " + getAvailableResources());
        }
        semaphore.release(count);
    }
    
    public int getAvailableResources() 
    {
        return availableResources;
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

        try 
        {
            Thread.sleep(1000); 
        } 
        catch (InterruptedException e) 
        {
        	e.printStackTrace();
        }

        manager.increaseCount(request);
    }
}

public class RaceCondition3 
{
    public static void main(String[] args) 
    {
        ResourceManager3 manager = new ResourceManager3();
        Thread t1 = new Process3(manager, 3);
        Thread t2 = new Process3(manager, 4);
        Thread t3 = new Process3(manager, 2);

        t1.start();
        t2.start();
        t3.start();

        try 
        {
            t1.join();
            t2.join();
            t3.join();
        } 
        catch (InterruptedException e) 
        {
        	e.printStackTrace();
        }

        System.out.println("Final available resources: " + manager.getAvailableResources());
    }
}

