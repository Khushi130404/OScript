package race_condition;

class ResourceManager2
{
    private static final int MAX_RESOURCES = 5;
    private int availableResources = MAX_RESOURCES; 

    public int decreaseCount(int count) 
    {
        if (availableResources < count) {  
            return -1; 
        } 
        else 
        {
            // **Race Condition here**: Multiple threads modifying availableResources at the same time
            availableResources -= count;
            return 0;
        }
    }

    public void increaseCount(int count) 
    {
        // **Race Condition here**: Another thread may modify availableResources at the same time
        availableResources += count;
    }

    public int getAvailableResources() 
    {
        return availableResources;
    }
}

class Process2 extends Thread 
{
    private ResourceManager2 manager;
    private int request;

    public Process2(ResourceManager2 manager, int request) 
    {
        this.manager = manager;
        this.request = request;
    }

    @Override
    public void run() 
    {
        if (manager.decreaseCount(request) == 0) 
        {  
            System.out.println(Thread.currentThread().getName() + " allocated " + request + " resources, Remaining: " + manager.getAvailableResources());

            try 
            { 
            	Thread.sleep(1000); 
            } 
            catch (InterruptedException e) 
            {
            	e.printStackTrace();
            }

            manager.increaseCount(request);
            System.out.println(Thread.currentThread().getName() + " released " + request + " resources, Remaining: " + manager.getAvailableResources());
        } 
        else 
        {
            System.out.println(Thread.currentThread().getName() + " request denied! Not enough resources.");
        }
    }
}

public class RaceCondition2 
{
    public static void main(String[] args) 
    {
        ResourceManager2 manager = new ResourceManager2();
        Thread t1 = new Process2(manager, 3);
        Thread t2 = new Process2(manager, 4);
        Thread t3 = new Process2(manager, 2);

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


