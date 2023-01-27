using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using LiveChartsCore;
using LiveChartsCore.SkiaSharpView;
using LiveChartsCore.SkiaSharpView.Painting;

namespace PlantWateringAndMonitoringSystem
{
    class SensorGraph
    {
        public ISeries[] Series { get; set; } = new ISeries[]
        {
            new LineSeries<double>
            {
                Values = new ObservableCollection<double> {3, 2, 4, 9, 2, 3},
                //Values = new double[] {3, 2, 4, 4, 9, 6, 32},

                Stroke = new SolidColorPaint(SkiaSharp.SKColors.Blue) {StrokeThickness = 4 },

                Fill = null
            }
        };

        public string pogamo = "poggusamogus";
    }
}
