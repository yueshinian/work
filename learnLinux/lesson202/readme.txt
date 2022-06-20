进程状态
    三态模型：就绪态（father：运行态，阻塞态；具备运行条件，等待处理器分配，就绪队列），运行态（进程占有处理器运行），阻塞态（不具备运行条件，等待条件运行wait or sleep）
    五态模型：新建态，。。。，终止态
ps aux / ajx
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
top -d
kill  -l
kill -9 pid
killall name