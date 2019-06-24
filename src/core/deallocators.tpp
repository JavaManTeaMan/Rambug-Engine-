template <class T> void arrdealloc(T *blk)
{
	delete[]blk;
}
template <class T> void blkdealloc(T *blk)
{
	delete blk;
}
template <class T> void dealloc(T *blk)
{
	free(blk);
}