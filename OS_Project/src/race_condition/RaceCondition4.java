package race_condition;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

class ResourceManager4
{
    private static final int MAX_RESOURCES = 5;
    private int availableResources = MAX_RESOURCES;
    private final Lock lock = new ReentrantLock(); 
    private final Condition condition = lock.newCondition();

    public void decreaseCount(int count) 
    {
        lock.lock();
        try 
        {
            while (availableResources < count) 
            {
                System.out.println(Thread.currentThread().getName() + " waiting for " + count + " resources.");
                condition.await(); 
            }

            availableResources -= count;
            System.out.println(Thread.currentThread().getName() + " allocated " + count + " resources, Remaining: " + getAvailableResources());
        } 
        catch (InterruptedException e) 
        {
            e.printStackTrace();
        } 
        finally 
        {
            lock.unlock(); 
        }
    }

    public void increaseCount(int count) 
    {
        lock.lock();
        try 
        {
            availableResources += count;
            System.out.println(Thread.currentThread().getName() + " released " + count + " resources, Remaining: " + getAvailableResources());
            condition.signalAll(); 
        } 
        finally
        {
            lock.unlock();
        }
    }
    
    public int getAvailableResources() 
    {
        return availableResources;
    }
}

class Process4 extends Thread 
{
    private ResourceManager4 manager;
    private int request;

    public Process4(ResourceManager4 manager, int request) 
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

public class RaceCondition4 
{
    public static void main(String[] args) 
    {
        ResourceManager4 manager = new ResourceManager4();
        Thread t1 = new Process4(manager, 3);
        Thread t2 = new Process4(manager, 4);
        Thread t3 = new Process4(manager, 2);

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
