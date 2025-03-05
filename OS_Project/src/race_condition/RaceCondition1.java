package race_condition;

class ResourceManager1
{
    private static final int MAX_RESOURCES = 5;
    private int availableResources = MAX_RESOURCES; 

    public int decreaseCount(int count) 
    {
        if (availableResources < count) 
        {
            return -1; 
        } 
        else 
        {
            availableResources -= count;
            return 0; 
        }
    }

    public void increaseCount(int count) 
    {
        availableResources += count;
    }

    public int getAvailableResources() 
    {
        return availableResources;
    }
}

class Process1 extends Thread 
{
    private ResourceManager1 manager;
    private int request;

    public Process1(ResourceManager1 manager, int request) 
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

public class RaceCondition1 
{
    public static void main(String[] args) 
    {
//    	System.out.println("hellooooooooooooooo.....!");
        ResourceManager1 manager = new ResourceManager1();
        Thread t1 = new Process1(manager, 3);
        Thread t2 = new Process1(manager, 4);
        Thread t3 = new Process1(manager, 2);

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

