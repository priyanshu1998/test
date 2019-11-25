#include "line_draw.hpp"

int abs(int x){
	if(x<0)return -x;
	else return x;
}

int round(double x){
    if(x>=0) return static_cast<int>(x+0.5);
    return static_cast<int>(-(-x+0.5));
}

line::line(point start,point end){
    a = start;
    b = end; 
}

std::vector<point> line::lineSimple(){
    std::vector<point> onLine;

    int dx = b.x - a.x,
        dy = b.y - a.y;

    //double m = static_cast<double>(dy)/static_cast<double>(dx);
    double x0,y0,y_double,x_double;
	if(abs(dy) <= abs(dx)){

        if(a.x > b.x){
            point t = b;
            b = a;
            a = t;
        }
        x0 = static_cast<double>(a.x);
        y0 = static_cast<double>(a.y);

        for(int x = a.x; x<= b.x; x++){
            y_double = y0 + (static_cast<double>(dy*(static_cast<double>(x) - x0))/dx);
			//setPixel(ROUND(x), ROUND(y));
            onLine.push_back({x,round(y_double)});
		}
	}
	else{
        if(a.y > b.y){
            point t = b;
            b = a;
            a = t;
        }
        y0 = static_cast<double>(a.y);
        x0 = static_cast<double>(a.x);
		
        for(int y = a.y; y<= b.y; y++){
            x_double = x0 + (static_cast<double>(dx*(static_cast<double>(y) - y0))/dy);
			//setPixel(ROUND(x), ROUND(y));
            onLine.push_back({round(x_double),y});
		}
	}

	return onLine;
}

std::vector<point> line::lineDDA(){
    std::vector<point> onLine;
    int dx = b.x - a.x,
        dy = b.y - a.y,
        steps;

    double xIncrement, yIncrement, x = a.x, y = a.y;

    if(abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);

    xIncrement = static_cast<double> (dx) / static_cast<double> (steps);
    yIncrement = static_cast<double> (dy) / static_cast<double> (steps);

    //setPixel(ROUND(x), ROUND(y));
	
    onLine.push_back({round(x), round(y)});


    for(int k = 0; k < steps; k++){
        x += xIncrement;
        y += yIncrement;
        //setPixel(ROUND(X), ROUND(Y));
        onLine.push_back({round(x), round(y)});
    }
	return onLine;
}

std::vector<point> line::Bres_pos_m(){
    std::vector<point> onLine;
	
    int x, y;
	int x_itr;

    if(a.x > b.x){
        point t = b;
		b = a;
		a = t;
	}

    x = a.x;
    y = a.y;
    x_itr = b.x - a.x;

    int dx = b.x - a.x, dy = b.y - a.y;

	if(abs(dy) > abs(dx)){
        line temp({a.y,a.x}, {b.y, b.x});
        std::vector<point> vec_temp = temp.Bres_pos_m();
		int t;
		for(auto &pt: vec_temp){
            t = pt.x;
            pt.x=pt.y;
            pt.y=t;
		}
		return vec_temp;
	}

	int p = 2 * dy - dx;
	int twoDy = 2*dy;
	int twoDyDx = 2*(dy-dx);

	

	onLine.push_back({x, y});
	while(x_itr--){
		x++;
		if(p<0){
			p += twoDy;
		}
		else{
			y++;
			p += twoDyDx;
		}
		onLine.push_back({x, y});
	}	
	return onLine;
}

std::vector<point> line::Bres_neg_m(){
    std::vector<point> onLine;
	
	int x, y;
	int x_itr;

    if(a.x > b.x){
        point t = b;
		b = a;
		a = t;
	}

    x = a.x;
    y = a.y;
    x_itr = b.x - a.x;


    int dx = b.x - a.x, dy = b.y - a.y;

	if(abs(dy) > abs(dx)){
        line temp({a.y,a.x}, {b.y, b.x});
        std::vector<point> vec_temp = temp.Bres_neg_m();
		int t;
		for(auto &pt: vec_temp){
            t = pt.x;
            pt.x=pt.y;
            pt.y=t;
		}
		return vec_temp;
	}

	int p = 2 * dy + dx;
	int twoDy = 2*dy;
	int twoDyDx = 2*(dy+dx);

	onLine.push_back({x, y});
	while(x_itr--){
		x++;
		if(p<0){
			y--;
			p += twoDyDx;
		}
		else{
			p+= twoDy;
		}
		onLine.push_back({x, y});
	}
	return onLine;
}

std::vector<point> line::lineBres(){
    int dx = b.x - a.x;
    int dy = b.y - a.y;

    //std::vector<point> onLine;

	if(dy!=0 && dx!=0){
		if(dy*dx > 0) return Bres_pos_m();
		else return Bres_neg_m();
	}
	else{
        std::vector<point> onLine;
        if(dx == 0){
            for(int y = ((a.y < b.y)?a.y:b.y); y<=((a.y > b.y)?a.y:b.y); y++){
                onLine.push_back({a.x, y});
			}
		}
		else{
            for(int x = ((a.x < b.x)?a.x:b.x); x<=((a.x > b.x)?a.x:b.x); x++){
                onLine.push_back({x, a.y});
			}
		}
        return onLine;
	}
    //return onLine;
}
