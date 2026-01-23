    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <sys/wait.h>

    int main(int argc, char *argv[])
    {
        int pid;
        pid = fork();

        if (pid < 0)
        {
            printf("fork failed\n");
            exit(1);
        }
        else if (pid == 0)
        {
            execlp("whoami", "whoami", NULL);
            exit(0);
        }
        else
        {
            printf("\nProcess ID is: %d\n", getpid());
            wait(NULL);
            exit(0);
        }
    }

    //SJF
    #include <stdio.h>

    int main()
    {
        int p[20], bt[20], wt[20], tat[20];
        int i, j, n, temp;
        float wtavg = 0, tatavg = 0;

        printf("Enter the number of processes: ");
        scanf("%d", &n);

        for(i = 0; i < n; i++)
        {
            p[i] = i;
            printf("Enter Burst Time for Process %d: ", i);
            scanf("%d", &bt[i]);
        }

        // Sort processes by burst time (SJF Non-preemptive)
        for(i = 0; i < n; i++)
        {
            for(j = i + 1; j < n; j++)
            {
                if(bt[i] > bt[j])
                {
                    temp = bt[i];
                    bt[i] = bt[j];
                    bt[j] = temp;

                    temp = p[i];
                    p[i] = p[j];
                    p[j] = temp;
                }
            }
        }

        wt[0] = 0;
        tat[0] = bt[0];
        tatavg = tat[0]; // include first process in average

        for(i = 1; i < n; i++)
        {
            wt[i] = wt[i - 1] + bt[i - 1];
            tat[i] = wt[i] + bt[i]; // correct formula for turnaround time
            wtavg += wt[i];
            tatavg += tat[i];
        }

        printf("\nPROCESS\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n");
        for(i = 0; i < n; i++)
            printf("P%d\t%d\t\t%d\t\t%d\n", p[i], bt[i], wt[i], tat[i]);

        printf("\nAverage Waiting Time: %.2f", wtavg / n);
        printf("\nAverage Turnaround Time: %.2f\n", tatavg / n);

        return 0;
    }



    //srtf
    #include <stdio.h>

    int main()
    {
        int n, i, time = 0, smallest;
        int at[20], bt[20], rt[20];
        int wt[20], tat[20];
        int complete = 0;
        float wtavg = 0, tatavg = 0;

        printf("Enter number of processes: ");
        scanf("%d", &n);

        for(i = 0; i < n; i++)
        {
            printf("Enter Arrival Time for P%d: ", i);
            scanf("%d", &at[i]);
            printf("Enter Burst Time for P%d: ", i);
            scanf("%d", &bt[i]);
            rt[i] = bt[i];
        }

        rt[19] = 9999; // Sentinel value

        while(complete != n)
        {
            smallest = 19;
            for(i = 0; i < n; i++)
            {
                if(at[i] <= time && rt[i] > 0 && rt[i] < rt[smallest])
                    smallest = i;
            }

            rt[smallest]--;
            time++;

            if(rt[smallest] == 0)
            {
                complete++;
                wt[smallest] = time - bt[smallest] - at[smallest];
                tat[smallest] = time - at[smallest];
                wtavg += wt[smallest];
                tatavg += tat[smallest];
            }
        }

        printf("\nPROCESS\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n");
        for(i = 0; i < n; i++)
            printf("P%d\t%d\t\t%d\t\t%d\n", i, bt[i], wt[i], tat[i]);

        printf("\nAverage Waiting Time: %.2f", wtavg / n);
        printf("\nAverage Turnaround Time: %.2f\n", tatavg / n);

        return 0;
    }


    //npp
    #include <stdio.h>

    int main()
    {
        int p[20], bt[20], pr[20], wt[20], tat[20];
        int i, j, n, temp;
        float wtavg = 0, tatavg = 0;

        printf("Enter the number of processes: ");
        scanf("%d", &n);

        for(i = 0; i < n; i++)
        {
            p[i] = i;
            printf("Enter Burst Time for Process %d: ", i);
            scanf("%d", &bt[i]);

            printf("Enter Priority for Process %d (lower number = higher priority): ", i);
            scanf("%d", &pr[i]);
        }

        for(i = 0; i < n; i++)
        {
            for(j = i + 1; j < n; j++)
            {
                if(pr[i] > pr[j])
                {
                    temp = pr[i];
                    pr[i] = pr[j];
                    pr[j] = temp;

                    temp = bt[i];
                    bt[i] = bt[j];
                    bt[j] = temp;

                    temp = p[i];
                    p[i] = p[j];
                    p[j] = temp;
                }
            }
        }

        wt[0] = 0;
        tat[0] = bt[0];

        for(i = 1; i < n; i++)
        {
            wt[i] = wt[i - 1] + bt[i - 1];
            tat[i] = tat[i - 1] + bt[i];
            wtavg += wt[i];
            tatavg += tat[i];
        }

        printf("\nPROCESS\tPRIORITY\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n");
        for(i = 0; i < n; i++)
            printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n",
                p[i], pr[i], bt[i], wt[i], tat[i]);

        printf("\nAverage Waiting Time: %.2f", wtavg / n);
        printf("\nAverage Turnaround Time: %.2f", tatavg / n);

        return 0;
    }


    //pp
    #include <stdio.h>

    int main()
    {
        int n, i, time = 0, smallest;
        int at[20], bt[20], rt[20], pr[20];
        int wt[20], tat[20];
        int complete = 0;
        float wtavg = 0, tatavg = 0;

        printf("Enter number of processes: ");
        scanf("%d", &n);

        for(i = 0; i < n; i++)
        {
            printf("Enter Arrival Time for P%d: ", i);
            scanf("%d", &at[i]);

            printf("Enter Burst Time for P%d: ", i);
            scanf("%d", &bt[i]);

            printf("Enter Priority for P%d: ", i);
            scanf("%d", &pr[i]);

            rt[i] = bt[i];
            wt[i] = 0;
            tat[i] = 0;
        }

        while(complete < n)
        {
            smallest = -1;

            for(i = 0; i < n; i++)
            {
                if(at[i] <= time && rt[i] > 0)
                {
                    if(smallest == -1 || pr[i] < pr[smallest])
                        smallest = i;
                }
            }

            if(smallest == -1)
            {
                time++;
                continue;
            }

            rt[smallest]--;
            time++;

            if(rt[smallest] == 0)
            {
                complete++;
                wt[smallest] = time - bt[smallest] - at[smallest];
                tat[smallest] = time - at[smallest];
                wtavg += wt[smallest];
                tatavg += tat[smallest];
            }
        }

        printf("\nPROCESS\tPRIORITY\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n");
        for(i = 0; i < n; i++)
            printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", i, pr[i], bt[i], wt[i], tat[i]);

        printf("\nAverage Waiting Time: %.2f", wtavg / n);
        printf("\nAverage Turnaround Time: %.2f", tatavg / n);

        return 0;
    }


    //rr
    #include <stdio.h>

    int main()
    {
        int n, i, time = 0, tq;
        int at[20], bt[20], rt[20];
        int wt[20], tat[20];
        int complete = 0;
        float wtavg = 0, tatavg = 0;
        int executed;

        printf("Enter number of processes: ");
        scanf("%d", &n);

        for(i = 0; i < n; i++)
        {
            printf("Enter Arrival Time for P%d: ", i);
            scanf("%d", &at[i]);

            printf("Enter Burst Time for P%d: ", i);
            scanf("%d", &bt[i]);

            rt[i] = bt[i];
            wt[i] = 0;
            tat[i] = 0;
        }

        printf("Enter Time Quantum: ");
        scanf("%d", &tq);

        while(complete < n)
        {
            executed = 0;

            for(i = 0; i < n; i++)
            {
                if(at[i] <= time && rt[i] > 0)
                {
                    executed = 1;

                    if(rt[i] > tq)
                    {
                        time += tq;
                        rt[i] -= tq;
                    }
                    else
                    {
                        time += rt[i];
                        wt[i] = time - bt[i] - at[i];
                        tat[i] = time - at[i];
                        wtavg += wt[i];
                        tatavg += tat[i];
                        rt[i] = 0;
                        complete++;
                    }
                }
            }

            if(executed == 0)
                time++;
        }

        printf("\nPROCESS\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n");
        for(i = 0; i < n; i++)
            printf("P%d\t%d\t\t%d\t\t%d\n", i, bt[i], wt[i], tat[i]);

        printf("\nAverage Waiting Time: %.2f", wtavg / n);
        printf("\nAverage Turnaround Time: %.2f", tatavg / n);

        return 0;
    }

