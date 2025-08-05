class BuildSegementTree {
public:
    void Build(int idx,int l,int r,vector<int>&arr,vector<int>&SegmentTree){

    if(l==r){
        SegmentTree[idx] = arr[l];
        return;
    }
    int mid = l + (r-l)/2;

    Build(2*idx+1,l,mid,arr,SegmentTree);
    Build(2*idx+2,mid+1,r,arr,SegmentTree);

    SegmentTree[idx] = max(SegmentTree[2*idx+1] , SegmentTree[2*idx+2]);
}

void Update(int idx,int i,int val,int l,int r,vector<int>&arr,vector<int>&SegmenTree){
       if(l==r){
         arr[i] = val;
         SegmenTree[idx] = arr[l];
         return;
       }

       int mid = l + (r-l)/2;

       if(i<=mid){
         Update(2*idx+1,i,val,l,mid,arr,SegmenTree);
       }
       else{
        Update(2*idx+2,i,val,mid+1,r,arr,SegmenTree);
       }

       SegmenTree[idx] = max(SegmenTree[2*idx+1] , SegmenTree[2*idx+2]);
}

int Query(int idx,int start,int end,int l,int r,vector<int>&SegmentTree){

    if(l>end || r<start) return 0;

    else if(l>=start && r<=end) return SegmentTree[idx];

    int mid = l + (r-l)/2;

    return max(Query(2*idx+1,start,end,l,mid,SegmentTree),Query(2*idx+2,start,end,mid+1,r,SegmentTree));
}
};