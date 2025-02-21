#include <string.h>

#include "ring_buffer.h"

#define RWP_SAFE_INTERVAL           (4)

#define RB_MEMCPY                   memcpy
#define RB_INT_DECLARATION()        
#define RB_INT_DISABLE()            
#define RB_INT_RESTORE()            

void rb_init(RB_PTR rb, uint8_t *addr, uint32_t capacity)
{
    RB_INT_DECLARATION();

    RB_INT_DISABLE();
    rb->address  = addr;
    rb->capacity = capacity;
    rb->wp       = 0;
    rb->rp       = 0;
    RB_INT_RESTORE();
}

void rb_clear(RB_PTR rb)
{
    RB_INT_DECLARATION();
 
    RB_INT_DISABLE();   
    rb->wp    = 0;
    rb->rp    = 0;
    RB_INT_RESTORE();
}

uint32_t rb_read(RB_PTR rb, uint8_t *buffer, uint32_t size, uint32_t count)
{
    uint32_t required_bytes = size * count;
    uint32_t read_bytes;
    uint32_t remain_bytes;
    uint32_t wp;
    RB_INT_DECLARATION();

    wp = rb->wp;

    if(required_bytes == 0) 
        return 0;

    if(wp >= rb->rp)
    {
        remain_bytes = wp - rb->rp;

        if(required_bytes > remain_bytes)
        {
            read_bytes = remain_bytes;
            RB_MEMCPY(buffer, &rb->address[rb->rp], read_bytes);

            RB_INT_DISABLE();
            rb->rp += read_bytes;
            RB_INT_RESTORE();
        }
        else
        {
            read_bytes = required_bytes;
            RB_MEMCPY(buffer, &rb->address[rb->rp], read_bytes);
            RB_INT_DISABLE();
            rb->rp += read_bytes;
            RB_INT_RESTORE();
        }
    }
    else
    {
        remain_bytes = rb->capacity - rb->rp;

        if(required_bytes > remain_bytes)
        {
            read_bytes = remain_bytes;
            RB_MEMCPY(buffer, &rb->address[rb->rp], read_bytes);

            if(required_bytes - read_bytes > wp)
            {
                RB_MEMCPY(buffer + read_bytes, &rb->address[0], wp);
                RB_INT_DISABLE();
                rb->rp = wp;
                RB_INT_RESTORE();
                read_bytes += wp;
            }
            else
            {
                RB_MEMCPY(buffer + read_bytes, &rb->address[0], required_bytes - read_bytes);
                RB_INT_DISABLE();
                rb->rp = required_bytes - read_bytes;
                RB_INT_RESTORE();
                read_bytes = required_bytes;
            }
        }
        else
        {
            read_bytes = required_bytes;
            RB_MEMCPY(buffer, &rb->address[rb->rp], read_bytes);
            RB_INT_DISABLE();
            rb->rp += read_bytes;
            RB_INT_RESTORE();
        }
    }

    return read_bytes;
}

uint32_t rb_write(RB_PTR rb, uint8_t *buffer, uint32_t size, uint32_t count)
{
    uint32_t remain_bytes;
    uint32_t write_bytes = size * count;
    uint32_t rp;
    RB_INT_DECLARATION();
    
    if(write_bytes == 0) 
        return 0;

    rp = rb->rp;

    if(rb->wp >= rp)
    {
        remain_bytes = rb->capacity - rb->wp + rp;

        if(remain_bytes >= write_bytes + RWP_SAFE_INTERVAL)
        {
            remain_bytes = rb->capacity - rb->wp;

            if(remain_bytes >= write_bytes)
            {
                RB_MEMCPY(&rb->address[rb->wp], buffer, write_bytes);
                RB_INT_DISABLE();
                rb->wp += write_bytes;
                RB_INT_RESTORE();
            }
            else
            {
                RB_MEMCPY(&rb->address[rb->wp], buffer, remain_bytes);
                RB_INT_DISABLE();
                rb->wp = write_bytes - remain_bytes;
                RB_INT_RESTORE();
                RB_MEMCPY(&rb->address[0], &buffer[remain_bytes], rb->wp);
            }
        }
        else
        {
            return 0;
        }
    }
    else
    {
        remain_bytes = rp - rb->wp;

        if(remain_bytes >= write_bytes + RWP_SAFE_INTERVAL)
        {
            RB_MEMCPY(&rb->address[rb->wp], buffer, write_bytes);
            RB_INT_DISABLE();
            rb->wp += write_bytes;
            RB_INT_RESTORE();
        }
        else
        {
            return 0;
        }
    }

    if(rb->wp >= rb->capacity && rb->rp)
    {
        RB_INT_DISABLE();
        rb->wp = 0;
        RB_INT_RESTORE();
    }

    return write_bytes;
}

uint32_t rb_get_fill_size(RB_PTR rb)
{
    uint32_t fill_size;

    fill_size = rb->wp >= rb->rp ? rb->wp - rb->rp : rb->capacity - rb->rp + rb->wp;

    return fill_size;
}

uint32_t rb_get_free_size(RB_PTR rb)
{
    uint32_t free_size;

    free_size = rb->wp >= rb->rp ? rb->capacity - rb->wp + rb->rp : rb->rp - rb->wp;

    return free_size > RWP_SAFE_INTERVAL ? free_size - RWP_SAFE_INTERVAL : 0;
}

