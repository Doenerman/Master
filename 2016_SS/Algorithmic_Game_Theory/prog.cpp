#include <iostream>
#include <set>
#include <vector>
#include <iterator>
#include <algorithm>
typedef std::set<int> set_type;
typedef std::set<set_type> powerset_type;
 
powerset_type powerset(set_type const& set)
{
  typedef set_type::const_iterator set_iter;
  typedef std::vector<set_iter> vec;
  typedef vec::iterator vec_iter;
 
  struct local
  {
    static int dereference(set_iter v) { return *v; }
  };
 
  powerset_type result;
 
  vec elements;
  do
  {
    set_type tmp;
    transform(elements.begin(), elements.end(),
                   std::inserter(tmp, tmp.end()),
                   local::dereference);
    result.insert(tmp);
    if (!elements.empty() && ++elements.back() == set.end())
    {
      elements.pop_back();
    }
    else
    {
      set_iter iter;
      if (elements.empty())
      {
        iter = set.begin();
      }
      else
      {
        iter = elements.back();
        ++iter;
      }
      for (; iter != set.end(); ++iter)
      {
        elements.push_back(iter);
      }
    }
  } while (!elements.empty());
 
  return result;
}
 
int main()
{
  int values[10] = { 50, 100, 75, 80, 70, 30, 40, 90, 160, 60 };
  set_type test_set(values, values+10);
 
  powerset_type test_powerset = powerset(test_set);
 
  for ( int i = 0; i < 6; i++){
    int c_u,c_l;
    switch(i) {
      case 0: c_l = 300; c_u = 500; break;
      case 1: c_l = 500; c_u = 600; break;
      case 2: c_l = 600; c_u = 650; break;
      case 3: c_l = 650; c_u = 675; break;
      case 4: c_l = 675; c_u = 680; break;
      case 5: c_l = 680; c_u = 900000000; break;
    }
    for (powerset_type::iterator iter = test_powerset.begin();
         iter != test_powerset.end();
         ++iter)
    {
      int sum = 0;
      for (set_type::iterator iter2 = iter->begin();
           iter2 != iter->end();
           ++iter2)
      {
          sum += *iter2;
      }
    
      if(c_l <= sum && sum < c_u && sum == c_l) {

        std::cout << c_l <<  " -> " << sum << " -> { ";
        char const* prefix = "";
        for (set_type::iterator iter2 = iter->begin();
             iter2 != iter->end();
             ++iter2)
        {
          std::cout << prefix << *iter2;
          prefix = ", ";
        }
        std::cout << " } \n";
      }
    }
  }
}
