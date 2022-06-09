#include <ds/circular_buffer.h>

struct circular_buf_t
{
	uint8_t* buffer;
	size_t head;
	size_t tail;
	size_t max;
	bool full;
};

static inline size_t advance_headtail_value(size_t value, size_t max)
{
	return (value + 1) % max;
}

static void advance_head_pointer(cbuf_handle_t me)
{
	if(circular_buf_full(me))
		me->tail = advance_headtail_value(me->tail, me->max);

	me->head = advance_headtail_value(me->head, me->max);
	me->full = (me->head == me->tail);
}

cbuf_handle_t circular_buf_init(uint8_t* buffer, size_t size)
{
	cbuf_handle_t cbuf = malloc(sizeof(circular_buf_t));

	cbuf->buffer = buffer;
	cbuf->max = size;
	circular_buf_reset(cbuf);

	assert(circular_buf_empty(cbuf));

	return cbuf;
}

void circular_buf_free(cbuf_handle_t me)
{
	free(me);
}

void circular_buf_reset(cbuf_handle_t me)
{
	me->head = 0;
	me->tail = 0;
	me->full = false;
}

size_t circular_buf_size(cbuf_handle_t me)
{
    size_t size = me->max;

	if(!circular_buf_full(me))
	{
		if(me->head >= me->tail)
			size = (me->head - me->tail);
		else
			size = (me->max + me->head - me->tail);
	}

	return size;
}

size_t circular_buf_capacity(cbuf_handle_t me)
{
	return me->max;
}

void circular_buf_put(cbuf_handle_t me, uint8_t data)
{
	me->buffer[me->head] = data;
	advance_head_pointer(me);
}

int32_t circular_buf_try_put(cbuf_handle_t me, uint8_t data)
{
	int32_t r = -1;

	if(!circular_buf_full(me))
	{
		me->buffer[me->head] = data;
		advance_head_pointer(me);
		r = 0;
	}

	return r;
}

int32_t circular_buf_get(cbuf_handle_t me, uint8_t* data)
{
	int32_t r = -1;

	if(!circular_buf_empty(me))
	{
		*data = me->buffer[me->tail];
		me->tail = advance_headtail_value(me->tail, me->max);
		me->full = false;
		r = 0;
	}

	return r;
}

bool circular_buf_empty(cbuf_handle_t me)
{
	return (!circular_buf_full(me) && (me->head == me->tail));
}

bool circular_buf_full(cbuf_handle_t me)
{
	return me->full;
}

int32_t circular_buf_peek(cbuf_handle_t me, uint8_t* data, uint32_t look_ahead_counter)
{
	int32_t r = -1;
	size_t pos;

	if(circular_buf_empty(me) || look_ahead_counter > circular_buf_size(me))
		return r;

	pos = me->tail;
	for(uint32_t i = 0; i < look_ahead_counter; i++)
	{
		data[i] = me->buffer[pos];
		pos = advance_headtail_value(pos, me->max);
	}

	return 0;
}